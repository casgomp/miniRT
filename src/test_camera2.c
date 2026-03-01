/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_camera2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:28:46 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/01 14:39:58 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_intersection	*intersection2(t_ray r, t_object *objp)
{
	double			a;
	double			b;
	double			c;
	double			discriminant;
	double			*sphere_to_ray;
	t_ray			local_r;
	t_intersection	*xs;

	local_r = transform_ray(r, objp->inverse);
	sphere_to_ray = local_r.ray_origin;
	local_r.ray_direction[3] = 0;//important to set this to 0, otherwise the dot_product_tuple will return a wrong result.
	sphere_to_ray[3] = 0;//important to set this to 0, otherwise the dot_product_tuple will return a wrong result.
	a = dot_product_tuple(local_r.ray_direction, local_r.ray_direction);
	b = 2 * dot_product_tuple(local_r.ray_direction, sphere_to_ray);
	c = dot_product_tuple(sphere_to_ray, sphere_to_ray) - 1;
	free(local_r.ray_origin);//free only local copies
	free(local_r.ray_direction);//free only local copies
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (NULL);
	xs = malloc(sizeof(t_intersection) * 2);//norminette too many variables...make function to create xs and store values.
	if (!xs)
		return (NULL);
	xs[0].t = (-b - sqrt(discriminant)) / (2 * a);
	xs[1].t = (-b + sqrt(discriminant)) / (2 * a);
	xs[0].obj = objp;
	xs[1].obj = objp;
	return (xs);
}

t_intersection	*intersect_list_append2(t_intersection *xs, 
							t_intersection *xslst, int *count, int *capacity)
{
	t_intersection	*newptr;
	int				i;

	newptr = NULL;
	if (*count + 2 > *capacity) //2 would eventually be a number passed to function based on object intersected(i.e. planes only have 1 intersection point).
	{
		*capacity = *capacity * 2;
		newptr = malloc(sizeof(t_intersection) * *capacity);
		if (!newptr)
			return (free(xs), free(xslst), NULL);
		i = -1;
		while (++i < *count)
			newptr[i] = xslst[i];
		free(xslst);
		xslst = newptr;
	}
	xslst[*count] = xs[0];
	xslst[*count + 1] = xs[1];
	*count += 2; //eventually change to the number of actual object(i.e. planes only have 1 intersection point).
	free(xs);
	return (xslst);
}

int	get_pixel_color2(t_ray r, t_object *world, t_light *light)//this function gets called for every ray.
{
	t_intersection	*xs;
	t_intersection	*xslst;
	t_intersection	*hit;
	int				xs_count;
	int				capacity;
	int				i;
	int				color;
	t_object		*curr;
	double			*hit_point;
	double			*w_normal;

	//create intersection list for every object
	xs_count = 0;
	capacity = 8;
	xslst = malloc(sizeof(t_intersection) * capacity);
	if (!xslst)
		return (0x000000); //should probably create a macro for black color.
	curr = world;
	while(curr)
	{
		xs = intersection2(r, curr);
		if (xs)
		{
			xslst = intersect_list_append2(xs, xslst, &xs_count, &capacity);
			if (!xslst)
				return (0x000000);
		}
		curr = curr->next;
	}
	//find the hit (hit logic = find smallest t: make separate function for norminette)
	//eventually with a function that sorts in ascending order and then simply choosing the first
	hit = NULL;
	i = -1;
	while (++i < xs_count)
	{
		if (xslst[i].t > 0.0001)
		{
			if (!hit || xslst[i].t < hit->t)
				hit = &xslst[i];
		}
	}
	color = 0x000000;
	if (hit)
	{
		color = 0xFF0000; //will change after light/shade.
		//world normal
		hit_point = ray_position(r, hit->t);//ray_position returns the intersection point in world space.
		w_normal = normal_at(hit->obj, hit_point);

		/*//having w_normal now can get reflection vector
		//should have in ray from parsing as light source? store in engine struct.
		double	*in = allocate_tuple(1,-1,0,0);//in is light vector
		if (!in)
			return(free(xslst), 1);
		double	*reflectv = reflect(in, w_normal);
		//printf("reflectv = %f,%f,%f,%f\n", reflectv[0],reflectv[1],reflectv[2],reflectv[3]);
		(void)reflectv;//get rid of this debugging void*/

		double	*eyev = subtract_tuple(r.ray_origin, hit_point);
		normalize_vector(eyev);
		double *colord = lighting(hit->obj->material, light, hit_point, eyev, w_normal);
		//color = transform colord into int.
		color = color_to_int(colord);
		free(w_normal);//free?
		//free(in);
		//free(reflectv);
	}
	free(xslst);
	return (color);
}

void	render_loop2(t_data *data, t_object *s, t_light *light)
{
	int				x;
	int				y;
	t_ray			r;
	double			world_x;
	double			world_y;
	const double	wall_z = 10;
	const double	wall_size = 7.0;
	double			pixel_size = wall_size / WIN_W;
	double			*target;
	int				color;

	r.ray_origin = allocate_tuple(0,0,-5,1); //camera origin (which is also the ray's origin)
	y = -1;
	while (++y < WIN_H)
	{
		world_y = (wall_size / 2) - (pixel_size * y);
		x = -1;
		while (++x < WIN_W)
		{
			world_x = -(wall_size / 2) + (pixel_size * x);

			target = allocate_tuple(world_x, world_y, wall_z, 1);
			r.ray_direction = subtract_tuple(target, r.ray_origin);
			normalize_vector(r.ray_direction);

			color = get_pixel_color2(r, s, light);
			img_pix_put(&(data->img), x, y, color);

			free(target);
			free(r.ray_direction);
		}
	}
	free(r.ray_origin);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_camera2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:28:46 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/04 13:34:57 by pecastro         ###   ########.fr       */
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

//int	get_pixel_color2(t_ray r, t_object *objp, t_light *light)//this function gets called for every ray.
double	*color_at(t_world *world, t_ray ray)
{
	t_intersection	*xs;
	t_intersection	*xslst;
	t_intersection	*hit;
	int				xs_count;
	int				capacity;
	int				i;
	t_object		*curr;
	//double			*hit_point;
	//double			*w_normal;
	t_comps			*comps;
	double			*colord;

	//create intersection list for every object
	xs_count = 0;
	capacity = 8;
	xslst = malloc(sizeof(t_intersection) * capacity);
	if (!xslst)
		return (BLACK_PIXEL);
	//curr = objp;
	curr = world->object;
	while(curr)
	{
		xs = intersection2(ray, curr);
		if (xs)
		{
			xslst = intersect_list_append2(xs, xslst, &xs_count, &capacity);
			if (!xslst)
				return (BLACK_PIXEL);
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

	//debugging
	printf("xs_count = %d\n", xs_count);
	colord = NULL;
	if (hit)
	{
		comps = prepare_computations(hit, ray);
		colord = shade_hit(world, comps);

		//hit_point = ray_position(ray, hit->t);//ray_position returns the intersection point in world space.
		//w_normal = normal_at(hit->obj, hit_point);

		/*//having w_normal now can get reflection vector
		//should have in ray from parsing as light source? store in engine struct.
		double	*in = allocate_tuple(1,-1,0,0);//in is light vector
		if (!in)
			return(free(xslst), 1);
		double	*reflectv = reflect(in, w_normal);
		//printf("reflectv = %f,%f,%f,%f\n", reflectv[0],reflectv[1],reflectv[2],reflectv[3]);
		(void)reflectv;//get rid of this debugging void*/

		//double	*eyev = subtract_tuple(r.ray_origin, hit_point);
		//normalize_vector(eyev);
		//double *colord = lighting(hit->obj->material, light, hit_point, eyev, w_normal);
		//color = transform colord into int.
		//color = color_to_int(colord);
		//free(w_normal);//free?
		//free(in);
		//free(reflectv);
	}
	//free function for freeing arrays
	free(xslst);//free each intersection, then free list
	return (colord);
}

void	render_loop2(t_data *data, t_world *w)
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
	double			*colord;
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

			//color = get_pixel_color2(r, w->object, w->light);
			colord = color_at(w, r);
			color = color_to_int(colord);
			img_pix_put(&(data->img), x, y, color);

			free(target);
			free(r.ray_direction);
		}
	}
	free(r.ray_origin);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

t_comps	*prepare_computations(t_intersection *intersection, t_ray ray)
{
	t_comps			*comps;
	double			*negative;

	comps = malloc(sizeof(t_comps));
	if (!comps)
		return (NULL);
	
	comps->t = intersection->t;
	comps->obj = intersection->obj;

	negative = allocate_tuple(-1,-1,-1,0);
	comps->point = ray_position(ray, comps->t);//point is the hit point
	comps->eyev = multiply_tuple_tuple(ray.ray_direction, negative);
	comps->normalv = normal_at(comps->obj, comps->point);

	if (dot_product_tuple(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = true;
		comps->normalv = multiply_tuple_tuple(comps->normalv, negative);
	}
	else
		comps->inside = false;

	free(negative);

	return (comps);
}//*/

double	*shade_hit(t_world *world, t_comps *comps)
{
	return (lighting(comps->obj->material, world->light, 
		comps->point, comps->eyev, comps->normalv));
}
/*
double	*color_at(t_world *world, t_ray ray)
{
	t_comps	*comps;
	double	*color;

	comps = prepare_computations(intersection, ray);
	color = shade_hit(world, comps);

	return (color);
}*/
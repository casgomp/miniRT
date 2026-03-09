/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_camera2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:28:46 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/09 15:16:46 by pecastro         ###   ########.fr       */
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

void	sort_intersections(t_intersection *xs, int *count)
{
	int	i;
	int	j;

	t_intersection	temp;

	i = 0;
	while (i < (*count) - 1)
	{
		j = 0;
		while (j < (*count) - i - 1)
		{
			if (xs[j].t > xs[j + 1].t)
			{
				temp = xs[j];
				xs[j] = xs[j + 1];
				xs[j + 1] = temp;
			}
			j ++;
		}
		i ++;
	}
}

t_intersection	*intersect_world(t_world *world, t_ray ray, int *count)
{
	t_intersection	*xs;
	t_intersection	*xslst;
	int				capacity;
	t_object		*curr;

	*count = 0;
	capacity = 8;
	xslst = malloc(sizeof(t_intersection) * capacity);
	if (!xslst)
		return (NULL);
	curr = world->object;
	while(curr)
	{
		xs = intersection2(ray, curr);
		if (xs)
		{
			xslst = intersect_list_append2(xs, xslst, count, &capacity);
			if (!xslst)
				return (NULL);
		}
		curr = curr->next;
	}
	sort_intersections(xslst, count);
	return(xslst);
}

//int	get_pixel_color2(t_ray r, t_object *objp, t_light *light)//this function gets called for every ray.
double	*color_at(t_world *world, t_ray ray)
{
	t_intersection	*xs;
	t_intersection	*hit;
	int				count;
	int				i;
	t_comps			*comps;
	double			*colord;

	//create intersection list for every object
	/*xs_count = 0;
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
	} */
	//find the hit (hit logic = find smallest t: make separate function for norminette)
	//eventually with a function that sorts in ascending order and then simply choosing the first
	
	xs = intersect_world(world, ray, &count);
	if (!xs)
		return (BLACK_PIXEL);
	
	hit = NULL;
	i = -1;
	while (++i < count)
	{
		if (xs[i].t > 0.0001)
		{
			hit = &xs[i];
			break ;
		}
	}
	//printf("xs_count = %d\n", xs_count);//debugging
	colord = NULL;
	if (hit)
	{
		comps = prepare_computations(hit, ray);
		colord = shade_hit(world, comps);
	}
	//free function for freeing arrays
	free(xs);//free each intersection, then free list
	return (colord);
}

//void	render_loop2(t_data *data, t_world *w)
void	render_loop2(t_data *data, t_world *w, t_camera *c)
{
	double			x;
	double			y;
	t_ray			*r;
	/* double			world_x;
	double			world_y;
	const double	wall_z = 10;
	const double	wall_size = 7.0;
	double			pixel_size = wall_size / WIN_W;
	double			*target; */
	double			*colord;
	int				color;

	printf("hsize=%f vsize=%f pixel_size=%f\n", c->hsize, c->vsize, c->pixel_size);
    printf("half_width=%f half_height=%f\n", c->half_width, c->half_height);

	//r.ray_origin = allocate_tuple(0,0,-5,1); //camera origin (which is also the ray's origin)
	y = -1.0;
	while (++y < c->vsize)
	{
		//world_y = (wall_size / 2) - (pixel_size * y);
		x = -1.0;
		while (++x < c->hsize)
		{
			/* world_x = -(wall_size / 2) + (pixel_size * x);

			target = allocate_tuple(world_x, world_y, wall_z, 1);
			r.ray_direction = subtract_tuple(target, r.ray_origin);
			normalize_vector(r.ray_direction); */

			//color = get_pixel_color2(r, w->object, w->light);

			r = ray_for_pixel(c, x, y);

			if (x == c->hsize/2 && y == c->vsize/2) // center pixel debug
                printf("center ray: origin=%f,%f,%f dir=%f,%f,%f\n",
                    r->ray_origin[0], r->ray_origin[1], r->ray_origin[2],
                    r->ray_direction[0], r->ray_direction[1], r->ray_direction[2]);
			
			colord = color_at(w, *r);
			
			if (x == c->hsize/2 && y == c->vsize/2)//debugging
                printf("center color: %f,%f,%f\n", 
                    colord ? colord[0] : -1,
                    colord ? colord[1] : -1,
                    colord ? colord[2] : -1);
			
					color = color_to_int(colord);
			img_pix_put(&(data->img), x, y, color);

			/* free(target);
			free(r.ray_direction); */
		}
	}
	//free(r.ray_origin);
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
		bool	in_shadow = false;
		return (lighting(comps->obj->material, world->light, 
		comps->point, comps->eyev, comps->normalv, in_shadow));

		//test ch.8
		/* bool	in_shadow = true;
		return (lighting(comps->obj->material, world->light, 
		comps->point, allocate_tuple(0,0,-1,0), allocate_tuple(0,0,-1,0), in_shadow)); */
}
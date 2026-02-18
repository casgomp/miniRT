/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:28:46 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/18 21:22:33 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*double	get_discriminant(double *ray_origin, double *ray_direction,
		double *sphere_center)*/
/*double	get_discriminant(t_ray r, t_sphere s)
{
	double	a;
	double	b;
	double	c;
	double	*sphere_to_ray;
	double	discriminant;

	sphere_to_ray = subtract_tuple(&s.center, &r.origin);
	a = dot_product_tuple(&r.direction, &r.direction);
	b = 2 * dot_product_tuple(&r.direction, sphere_to_ray);
	c = dot_product_tuple(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2) - (4 * a * c);
	return (discriminant);
}*/

t_intersection	*intersection(t_ray r, t_sphere *s)
{
	double			a;
	double			b;
	double			c;
	double			*sphere_to_ray;
	double			discriminant;
	t_intersection	*xs;

	sphere_to_ray = subtract_tuple(&s->center, &r.origin);
	a = dot_product_tuple(&r.direction, &r.direction);
	b = 2 * dot_product_tuple(&r.direction, sphere_to_ray);
	c = dot_product_tuple(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (NULL);
	xs = malloc(sizeof(t_intersection) * 2);
	if (!xs)
		return (NULL);
	//norminette too many variables...make function to create xs and store values.
	xs[0].t = (-b - sqrt(discriminant)) / (2 * a);
	xs[1].t = (-b + sqrt(discriminant)) / (2 * a);
	xs[0].sphere = s;
	xs[1].sphere = s;
	return (xs);
}

t_intersection	*intersect_list_append(t_intersection *xs, 
							t_intersection *xslst, int *count, int *capacity)
{
	t_intersection	*newptr;
	int				i;

	newptr = NULL;
	if (*count + 2 > *capacity) //2 would eventually be a number passed to function based on object intersected
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
	*count += 2; //eventually chnage to the number of actual object.
	free(xs);
	return (xslst);
}

int	get_pixel_color(t_ray r, t_sphere *s)//this function gets called for every ray
{
	t_intersection	*xs;
	t_intersection	*xslst;
	t_intersection	*hit;
	int				xs_count;
	int				capacity;
	int				i;
	int				color;

	//create intersection list for every object
	xs_count = 0;
	capacity = 8;
	while (++i < 1) //eventually < number of objects in scene
	{
		xs = intersection(r, s);
		if (xs)
		{
			xslst = intersect_list_append(xs, xslst, xs_count, &capacity);
			if (!xslst)
				return (NULL);
		}
	}

	//find the hit
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
		color = 0xFF0000;
	return (free(xslst), color);
}

void	render_loop(t_data *data, t_sphere *s)
{
	int		x;
	int		y;
	int		color;
	t_ray	r;

	r.origin = allocate_tuple(0,0,-5,1); //camera origin (which is also the ray's origin)
	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			get_pixel_color(r, s);
			img_pix_put(&(data->img), x, y, color);
		}
	}
}
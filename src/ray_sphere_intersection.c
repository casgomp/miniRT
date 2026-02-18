/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:28:46 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/18 15:49:19 by pecastro         ###   ########.fr       */
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
							t_intersection *xslst, int xs_count, int *capacity)
{
	t_intersection	*newptr;

	newptr = NULL;
	if (xs_count > *capacity)
	{
		*capacity == *capacity * 2;
		newptr = malloc(sizeof(t_intersection) * *capacity);
		if (!newptr)
			return (free(xs), NULL);
		memcpy(newptr, xslst, xs_count - 2);
		newptr[xs_count - 1] = ;
		newptr[xs_count] = ;
	}
	//memcpy stuff to newptr
	//add xs to newptr

	xslst = newptr;
	free(xs);
	return (xslst);
}

void	render_loop(void)/*either void or take scene arguments*/
{
	t_intersection	*xs;
	t_intersection	*xslst;
	t_ray			r; //
	t_sphere		s; //
	int				obj_count;//obj_ct wont work with complex scene?
	int				xs_count;
	int				capacity;
	int				i;

	xs_count = 0;
	capacity = 8;
	while (++i < obj_count)
	{
		xs = intersection(r, &s);
		if (xs)
		{
			xs_count += 2; //this wont work whith complex scene (plane xs=1 not 2)
			xslst = intersect_list_append(xs, xslst, xs_count, &capacity);
			if (!xslst)
				return (NULL);// first free list?
		}
	}
	//free xs in this function
	//do something with t and then free
	//group intersections

	//identify the hit

	//if hits exists paint red otherwise paint black

	//free
}

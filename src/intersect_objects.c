/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:08:11 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/11 19:57:28 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_intersection	*intersection_sphere(t_intersection *xs, t_object *sphere
	, double *ray_origin, double *ray_dir)
{
	double		a;
	double		b;
	double		c;
	double		discriminant;

	ray_origin[3] = 0;
	a = dot_product_tuple(ray_dir, ray_dir);
	b = 2 * dot_product_tuple(ray_dir, ray_origin);
	c = dot_product_tuple(ray_origin, ray_origin) - 1;
	discriminant = b * b - (4 * a * c);
	free(ray_origin);
	free(ray_dir);
	if (discriminant < 0)
		return (NULL);
	xs[0].t = (-b - sqrt(discriminant)) / (2 * a);
	xs[1].t = (-b + sqrt(discriminant)) / (2 * a);
	xs[0].obj = sphere;
	xs[1].obj = sphere;
	return (xs);
}

t_intersection	*intersection_plane(t_intersection *xs, t_object *plane
	, double *ray_origin, double *ray_dir)
{
	if (fabs(ray_dir[1]) < EPSILON)
		return (free(ray_origin), free(ray_dir), NULL);
	else
	{
		xs[0].t = (-1 * (ray_origin[1])) / ray_dir[1];
		xs[0].obj = plane;
		xs[1] = (t_intersection){0};
		return (free(ray_origin), free(ray_dir), xs);
	}
}

t_intersection	*intersection_cylinder(t_intersection *xs, t_object *cyl,
	double *ray_origin, double *ray_dir)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = ray_dir[0] * ray_dir[0] + ray_dir[2] * ray_dir[2];
	if (fabs(a) < EPSILON)
		return (intersection_caps(xs, cyl, ray_origin, ray_dir)
			, free(ray_origin), free(ray_dir), NULL);
	b = 2 * ray_origin[0] * ray_dir[0]
		+ 2 * ray_origin[2] * ray_dir[2];
	c = ray_origin[0] * ray_origin[0]
		+ ray_origin[2] * ray_origin[2] - 1;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (free(ray_origin), free(ray_dir), NULL);
	xs[0].t = (-b - sqrt(discriminant)) / (2 * a);
	xs[1].t = (-b + sqrt(discriminant)) / (2 * a);
	if (xs[0].t > xs[1].t)
		ft_swap(&xs[0].t, &xs[1].t);
	truncate_cylinder(ray_origin, ray_dir, cyl, xs);
	intersection_caps(xs, cyl, ray_origin, ray_dir);
	return (free(ray_origin), free(ray_dir), xs);
}

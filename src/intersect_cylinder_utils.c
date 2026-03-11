/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:06:24 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/11 19:56:10 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	cap_check(double *ray_origin, double *ray_dir, double t)
{
	double	x;
	double	z;
	double	check;

	x = ray_origin[0] + t * ray_dir[0];
	z = ray_origin[2] + t * ray_dir[2];
	check = (x * x) + (z * z);
	return (check);
}

void	intersect_cap_min(t_intersection *xs, t_object *cyl,
		double *ray_origin, double *ray_dir)
{
	double	min;
	double	t;
	double	check;

	min = -cyl->scale[2] / 2;
	t = (min - ray_origin[1]) / ray_dir[1];
	check = cap_check(ray_origin, ray_dir, t);
	if (check <= 1)
	{
		if (!xs[0].obj)
		{
			xs[0].t = t;
			xs[0].obj = cyl;
		}
		else if (!xs[1].obj)
		{
			xs[1].t = t;
			xs[1].obj = cyl;
		}
	}
}

void	intersect_cap_max(t_intersection *xs, t_object *cyl,
		double *ray_origin, double *ray_dir)
{
	double	max;
	double	t;
	double	check;

	max = cyl->scale[2] / 2;
	t = (max - ray_origin[1]) / ray_dir[1];
	check = cap_check(ray_origin, ray_dir, t);
	if (check <= 1)
	{
		if (!xs[0].obj)
		{
			xs[0].t = t;
			xs[0].obj = cyl;
		}
		else if (!xs[1].obj)
		{
			xs[1].t = t;
			xs[1].obj = cyl;
		}
	}
}

void	intersection_caps(t_intersection *xs, t_object *cyl,
		double *ray_origin, double *ray_dir)
{
	if (fabs(ray_dir[1]) < EPSILON)
		return ;
	intersect_cap_min(xs, cyl, ray_origin, ray_dir);
	intersect_cap_max(xs, cyl, ray_origin, ray_dir);
}

void	truncate_cylinder(double *origin, double *dir,
	t_object *cyl, t_intersection *xs)
{
	double	y0;
	double	y1;
	double	max;
	double	min;

	y0 = origin[1] + xs[0].t * dir[1];
	y1 = origin[1] + xs[1].t * dir[1];
	min = (-cyl->scale[2] / 2);
	max = (cyl->scale[2] / 2);
	xs[0].obj = NULL;
	xs[1].obj = NULL;
	if (y0 > min && y0 < max)
		xs[0].obj = cyl;
	if (y1 > min && y1 < max)
		xs[1].obj = cyl;
}

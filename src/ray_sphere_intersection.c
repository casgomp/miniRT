/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:28:46 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/16 22:25:47 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	get_discriminant(double *ray_origin, double *ray_direction,
		double *sphere_center)
{
	double	a;
	double	b;
	double	c;
	double	*sphere_to_ray;
	double	discriminant;

	sphere_to_ray = subtract_tuple(ray_origin, sphere_center);
	a = dot_product_tuple(ray_direction, ray_direction);
	b = 2 * dot_product_tuple(ray_direction, sphere_to_ray);
	c = dot_product_tuple(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2) - (4 * a * c);
	return (discriminant);
}

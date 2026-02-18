/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:28:46 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/17 21:55:45 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*get_discriminant(double *ray_origin, double *ray_direction,
	double *sphere_origin)
{
	double	*sphere_to_ray;
	double	*discriminant;

	discriminant = allocate_tuple(0, 0, 0, 0);
	if (!discriminant)
		return (NULL);
	sphere_to_ray = subtract_tuple(ray_origin, sphere_origin);
	discriminant[0] = dot_product_tuple(ray_direction, ray_direction);
	discriminant[1] = 2 * dot_product_tuple(ray_direction, sphere_to_ray);
	discriminant[2] = dot_product_tuple(sphere_to_ray, sphere_to_ray) - 1;
	discriminant[3] = pow(discriminant[1], 2)
		- (4 * discriminant[0] * discriminant[2]);
	free(sphere_to_ray);
	return (discriminant);
}

double	*ray_sphere_t(double *ray_origin, double *ray_direction,
		double *sphere_center)
{
	double		*discriminant;
	double		a;
	double		b;
	double		c;
	double		*t;

	discriminant = get_discriminant(ray_origin, ray_direction, sphere_center);
	if (discriminant < 0)
		return (NULL);
	a = discriminant[0];
	b = discriminant[1];
	c = discriminant[2];
	t = malloc (2 * sizeof(double));
	if (!t)
		return (NULL);
	t[0] = (-1 * b - sqrt(discriminant[3])) / (2 * a);
	t[1] = (-1 * b - sqrt(discriminant[3])) / (2 * a);
	free(discriminant);
	return (t);
}

double	*multiply_scalar(double *tuple, double scalar)
{
	double	*result;

	result = allocate_tuple(0, 0, 0, 0);
	if (!result)
		return (NULL);
	result[0] = tuple[0] * scalar;
	result[1] = tuple[1] * scalar;
	result[2] = tuple[2] * scalar;
	result[3] = tuple[3] * scalar;
	return (result);
}

double	**ray_sphere_points(double *ray_origin, double *ray_direction,
		double *t)
{
	double	*first_intersection;
	double	*scalar_1;
	double	*second_intersection;
	double	*scalar_2;
	double	**intersection_arr;

	scalar_1 = multiply_scalar(ray_direction, t[0]);
	scalar_2 = multiply_scalar(ray_direction, t[1]);
	if (!scalar_1 || !scalar_2)
		return (NULL);
	first_intersection = add_tuple(ray_origin, scalar_1);
	if (!first_intersection)
		return (NULL);
	second_intersection = add_tuple(ray_origin, scalar_2);
	if (!second_intersection)
		return (NULL);
	free(scalar_1);
	free(scalar_2);
	intersection_arr = malloc(2 * sizeof(double *));
	if (!intersection_arr)
		return (NULL);
	intersection_arr[0] = first_intersection;
	intersection_arr[1] = second_intersection;
	return (intersection_arr);
}

t_ray	construct_ray(double *ray_origin, double *ray_direction)
{
	t_ray	ray;

	ray = (t_ray){0};
	ray.ray_origin = ray_origin;
	ray.ray_direction = ray_direction;

}

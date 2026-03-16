/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:21:06 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/16 20:51:41 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*normal_at(t_object *object, double *world_point)
{
	double	*local_point;
	double	*local_normal;
	double	**transposed_inverse;
	double	*world_normal;

	local_point = multiply_matrix_tuple(object->inverse, world_point);
	local_normal = NULL;
	if (object->object_type == SPHERE)
		local_normal = allocate_tuple(local_point[0],
				local_point[1], local_point[2], 0);
	else if (object->object_type == CYLINDER)
	{
		double dist = local_point[0] * local_point[0]
					+ local_point[2] * local_point[2];

		if (dist < 1 && local_point[1] >= object->scale[1] / 2 - EPSILON)
			local_normal = allocate_tuple(0, 1, 0, 0);
		else if (dist < 1 && local_point[1] <= (-object->scale[1] / 2) + EPSILON)
			local_normal = allocate_tuple(0, -1, 0, 0);
		else
			local_normal = allocate_tuple(local_point[0], 0, local_point[2], 0);
	}
	else if (object->object_type == PLANE)
		local_normal = allocate_tuple(0, 1, 0, 0);

	if (!local_normal)
	{
		free(local_point);
		return (NULL);
	}

	transposed_inverse = transpose_grid(object->inverse);
	world_normal = multiply_matrix_tuple(transposed_inverse, local_normal);
	if (!world_normal)
	{
		free(local_point);
		free(local_normal);
		free_grid(transposed_inverse);
		return (NULL);
	}
	world_normal[3] = 0;
	normalize_vector(world_normal);
	free(local_point);
	free(local_normal);
	free_grid(transposed_inverse);
	return (world_normal);
}

double	*ray_position(t_ray r, double t)
{
	double	*scaled_dir;
	double	*pos;

	scaled_dir = multiply_scalar(r.ray_direction, t);
	pos = add_tuple(r.ray_origin, scaled_dir);
	free (scaled_dir);
	return (pos);
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
	negative = allocate_tuple(-1, -1, -1, 0);
	comps->point = ray_position(ray, comps->t);
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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:21:06 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/19 15:46:12 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*compute_local_normal(t_object *object, double *local_pnt)
{
	double		*local_normal;
	double		dist;

	local_normal = NULL;
	if (object->object_type == SPHERE)
		local_normal = allocate_tuple(local_pnt[0], local_pnt[1],
				local_pnt[2], 0);
	else if (object->object_type == CYLINDER)
	{
		dist = local_pnt[0] * local_pnt[0] + local_pnt[2] * local_pnt[2];
		if ((dist < 1.0)
			&& (local_pnt[1] >= (object->scale[1] / 2.0 - EPSILON)))
			local_normal = allocate_tuple(0, 1, 0, 0);
		else if ((dist < 1.0)
			&& (local_pnt[1] <= (-object->scale[1] / 2.0 + EPSILON)))
			local_normal = allocate_tuple(0, -1, 0, 0);
		else
			local_normal = allocate_tuple(local_pnt[0], 0, local_pnt[2], 0);
	}
	else if (object->object_type == PLANE)
		local_normal = allocate_tuple(0, 1, 0, 0);
	return (local_normal);
}

double	*normal_at(t_object *object, double *world_point)
{
	double	*local_point;
	double	*local_normal;
	double	**transposed_inverse;
	double	*world_normal;

	local_point = multiply_matrix_tuple(object->inverse, world_point);
	if (local_point == NULL)
		return (NULL);
	local_normal = compute_local_normal(object, local_point);
	if (local_normal == NULL)
		return (free(local_point), NULL);
	transposed_inverse = transpose_grid(object->inverse);
	if (transposed_inverse == NULL)
		return (free(local_point), free(local_normal), NULL);
	world_normal = multiply_matrix_tuple(transposed_inverse, local_normal);
	if (world_normal == NULL)
		return (free(local_point), free(local_normal)
			, free_grid(transposed_inverse), NULL);
	world_normal[3] = 0;
	normalize_vector(world_normal);
	return (free(local_point), free(local_normal)
		, free_grid(transposed_inverse), world_normal);
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
	double			*tmp;

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
		tmp = multiply_tuple_tuple(comps->normalv, negative);
		free(comps->normalv);
		comps->normalv = tmp;
	}
	else
		comps->inside = false;
	free(negative);
	return (comps);
}

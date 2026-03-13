/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:08:19 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/13 14:43:50 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	transform_ray(t_ray r, double **m)
{
	t_ray	new_ray;

	new_ray.ray_origin = multiply_matrix_tuple(m, r.ray_origin);
	new_ray.ray_direction = multiply_matrix_tuple(m, r.ray_direction);
	return (new_ray);
}

t_intersection	*intersection(t_ray r, t_object *objp)
{
	t_ray			local_r;
	t_intersection	*xs;

	local_r = transform_ray(r, objp->inverse);
	xs = malloc(sizeof(t_intersection) * 2);
	if (!xs)
		return (NULL);
	if (objp->object_type == SPHERE)
		return (intersection_sphere(xs, objp, local_r.ray_origin
				, local_r.ray_direction));
	else if (objp->object_type == PLANE)
		return (intersection_plane(xs, objp, local_r.ray_origin
				, local_r.ray_direction));
	else if (objp->object_type == CYLINDER)
		return (intersection_cylinder(xs, objp, local_r.ray_origin
				, local_r.ray_direction));
	else
		return (free(xs), NULL);
}

t_intersection	*intersect_list_append(t_intersection *xs,
							t_intersection *xslst, int *count, int *capacity)
{
	t_intersection	*newptr;
	int				i;

	newptr = NULL;
	if (*count + 2 > *capacity)
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
	*count += 2;
	free(xs);
	return (xslst);
}

void	sort_intersections(t_intersection *xs, int *count)
{
	t_intersection	temp;
	int				i;
	int				j;

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
	while (curr)
	{
		xs = intersection(ray, curr);
		if (xs)
		{
			xslst = intersect_list_append(xs, xslst, count, &capacity);
			if (!xslst)
				return (NULL);
		}
		curr = curr->next;
	}
	sort_intersections(xslst, count);
	return (xslst);
}

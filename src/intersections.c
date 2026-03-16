/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:08:19 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/16 14:23:06 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_intersection	*intersection(t_ray r, t_object *objp)
{
	double			a;
	double			b;
	double			c;
	double			discriminant;
	t_ray			local_r;

	local_r = transform_ray(r, objp->inverse);
	local_r.ray_direction[3] = 0;
	local_r.ray_origin[3] = 0;
	a = dot_product_tuple(local_r.ray_direction, local_r.ray_direction);
	b = 2 * dot_product_tuple(local_r.ray_direction, local_r.ray_origin);
	c = dot_product_tuple(local_r.ray_origin, local_r.ray_origin) - 1;
	free(local_r.ray_origin);
	free(local_r.ray_direction);
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (NULL);
	return (get_xs(objp, discriminant, a, b));
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

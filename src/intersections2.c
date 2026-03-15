/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:37:20 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/15 14:21:08 by pecastro         ###   ########.fr       */
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

t_intersection	*get_xs(t_object *objp, double discriminant, double a, double b)
{
	t_intersection	*xs;

	xs = malloc(sizeof(t_intersection) * 2);
	if (!xs)
		return (NULL);
	xs[0].t = (-b - sqrt(discriminant)) / (2 * a);
	xs[1].t = (-b + sqrt(discriminant)) / (2 * a);
	xs[0].obj = objp;
	xs[1].obj = objp;
	return (xs);
}

void	sort_intersections(t_intersection *xs, int *count)
{
	int				i;
	int				j;
	t_intersection	temp;

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

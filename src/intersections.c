/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:08:19 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/09 19:02:30 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray   transform_ray(t_ray r, double **m)//double or a simple t_matrix works too.
{
    t_ray   new_ray;

    new_ray.ray_origin = multiply_matrix_tuple(m, r.ray_origin);
    new_ray.ray_direction = multiply_matrix_tuple(m, r.ray_direction);
    return (new_ray);
}

t_intersection	*intersection(t_ray r, t_object *objp)
{
	double			a;
	double			b;
	double			c;
	double			discriminant;
	double			*sphere_to_ray;
	t_ray			local_r;
	t_intersection	*xs;

	local_r = transform_ray(r, objp->inverse);
	sphere_to_ray = local_r.ray_origin;
	local_r.ray_direction[3] = 0;//important to set this to 0, otherwise the dot_product_tuple will return a wrong result.
	sphere_to_ray[3] = 0;//important to set this to 0, otherwise the dot_product_tuple will return a wrong result.
	a = dot_product_tuple(local_r.ray_direction, local_r.ray_direction);
	b = 2 * dot_product_tuple(local_r.ray_direction, sphere_to_ray);
	c = dot_product_tuple(sphere_to_ray, sphere_to_ray) - 1;
	free(local_r.ray_origin);//free only local copies
	free(local_r.ray_direction);//free only local copies
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (NULL);
	xs = malloc(sizeof(t_intersection) * 2);//norminette too many variables...make function to create xs and store values.
	if (!xs)
		return (NULL);
	xs[0].t = (-b - sqrt(discriminant)) / (2 * a);
	xs[1].t = (-b + sqrt(discriminant)) / (2 * a);
	xs[0].obj = objp;
	xs[1].obj = objp;
	return (xs);
}

t_intersection	*intersect_list_append(t_intersection *xs, 
							t_intersection *xslst, int *count, int *capacity)
{
	t_intersection	*newptr;
	int				i;

	newptr = NULL;
	if (*count + 2 > *capacity) //2 would eventually be a number passed to function based on object intersected(i.e. planes only have 1 intersection point).
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
	*count += 2; //eventually change to the number of actual object(i.e. planes only have 1 intersection point).
	free(xs);
	return (xslst);
}

void	sort_intersections(t_intersection *xs, int *count)
{
	int	i;
	int	j;

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
	while(curr)
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
	return(xslst);
}
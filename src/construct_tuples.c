/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_tuples.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:42:12 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/18 10:06:23 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*allocate_tuple(double x, double y, double z, double w)
{
	double		*coordinate;

	coordinate = malloc(4 * sizeof(double));
	if (!coordinate)
		return (perror(MALL_ERR), NULL);
	coordinate[0] = x;
	coordinate[1] = y;
	coordinate[2] = z;
	coordinate[3] = w;
	return (coordinate);
}

void	normalize_vector(t_tuple *vector)
{
	double	magnitude;

	magnitude = 0;
	magnitude = sqrtf(pow(vector->tuple[0], 2) + pow(vector->tuple[1], 2)
			+ pow(vector->tuple[2], 2) + pow(vector->tuple[3], 2));
	vector->magnitude = magnitude;
	vector->unit_vector = malloc(4 * sizeof(double));
	if (!vector->unit_vector)
		return ;
	vector->unit_vector[0] = vector->tuple[0] / magnitude;
	vector->unit_vector[1] = vector->tuple[1] / magnitude;
	vector->unit_vector[2] = vector->tuple[2] / magnitude;
	vector->unit_vector[3] = vector->tuple[3] / magnitude;
}

t_tuple	construct_tuple(double x, double y, double z, double w)
{
	t_tuple		tuple;

	tuple = (t_tuple){0};
	tuple.tuple = allocate_tuple(x, y, z, w);
	if (!tuple.tuple)
		return((t_tuple){0});
	if (w == 0)
	{
		tuple.tuple_type = VECTOR;
		normalize_vector(&tuple);
		if (!tuple.unit_vector)
			return (perror(MALL_ERR), free(tuple.tuple), (t_tuple){0});
	}
	else
		tuple.tuple_type = POINT;
	return (tuple);
}

void	free_tuple(t_tuple *tuple)
{
	free(tuple->tuple);
	free(tuple->unit_vector);
}

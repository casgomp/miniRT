/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_tuples.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:42:12 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/16 20:48:14 by aabdella         ###   ########.fr       */
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

double	get_vector_magnitude(double *vector)
{
	double	magnitude;

	magnitude = sqrt((vector[0] * vector[0])
			+ (vector[1] * vector[1])
			+ (vector[2] * vector[2]));
	return (magnitude);
}

void	apply_normalize_vector(double *vector, double magnitude)
{
	vector[0] /= magnitude;
	vector[1] /= magnitude;
	vector[2] /= magnitude;
	vector[3] = 0;
}

void	normalize_vector(double *vector)
{
	double	magnitude;

	magnitude = get_vector_magnitude(vector);
	if (magnitude == 0)
		return ;
	apply_normalize_vector(vector, magnitude);
}

void	free_tuple(t_tuple *tuple)
{
	free(tuple->tuple);
	free(tuple->unit_vector);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tuple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:43:52 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/16 18:28:07 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * (PI / 180.0));
}

double	radians_to_degrees(double radians)
{
	return (radians * (180.0 / PI));
}

double	**tuple_to_matrix(double *tuple)
{
	double	**tuple_matrix;

	tuple_matrix = allocate_grid(4);
	if (!tuple_matrix)
		return (NULL);
	tuple_matrix[0][0] = tuple[0];
	tuple_matrix[1][0] = tuple[1];
	tuple_matrix[2][0] = tuple[2];
	tuple_matrix[3][0] = tuple[3];
	return (tuple_matrix);
}

double	*matrix_to_tuple(double **grid)
{
	double	*tuple;

	tuple = allocate_tuple(grid[0][0], grid[1][0], grid[2][0], grid[3][0]);
	if (!tuple)
		return (NULL);
	return (tuple);
}

double	*cross_product(double *vector_1, double *vector_2)
{
	double	*result;

	result = malloc(4 * sizeof(double));
	if (!result)
		return (perror(MALL_ERR), NULL);
	result[0] = (vector_1[1] * vector_2[2]) - (vector_1[2] * vector_2[1]);
	result[1] = (vector_1[2] * vector_2[0]) - (vector_1[0] * vector_2[2]);
	result[2] = (vector_1[0] * vector_2[1]) - (vector_1[1] * vector_2[0]);
	result[3] = 0;
	return (result);
}

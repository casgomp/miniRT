/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_tuple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:43:24 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/16 21:44:12 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*rotate_tuple_x(double *tuple, double angle)
{
	double	**tuple_matrix;
	double	**rotation_matrix;
	double	**transformed_matrix;
	double	*result;

	tuple_matrix = tuple_to_matrix(tuple);
	rotation_matrix = rotation_x(angle);
	transformed_matrix = matrix_multiply(rotation_matrix, tuple_matrix);
	result = matrix_to_tuple(transformed_matrix);
	if (!tuple_matrix || !rotation_matrix || !transformed_matrix || !result)
		return (NULL);
	free_grid(tuple_matrix);
	free_grid(rotation_matrix);
	free_grid(transformed_matrix);
	return (result);
}

double	*rotate_tuple_y(double *tuple, double angle)
{
	double	**tuple_matrix;
	double	**rotation_matrix;
	double	**transformed_matrix;
	double	*result;

	tuple_matrix = tuple_to_matrix(tuple);
	rotation_matrix = rotation_y(angle);
	transformed_matrix = matrix_multiply(rotation_matrix, tuple_matrix);
	result = matrix_to_tuple(transformed_matrix);
	if (!tuple_matrix || !rotation_matrix || !transformed_matrix || !result)
		return (NULL);
	free_grid(tuple_matrix);
	free_grid(rotation_matrix);
	free_grid(transformed_matrix);
	return (result);
}

double	*rotate_tuple_z(double *tuple, double angle)
{
	double	**tuple_matrix;
	double	**rotation_matrix;
	double	**transformed_matrix;
	double	*result;

	tuple_matrix = tuple_to_matrix(tuple);
	rotation_matrix = rotation_z(angle);
	transformed_matrix = matrix_multiply(rotation_matrix, tuple_matrix);
	result = matrix_to_tuple(transformed_matrix);
	if (!tuple_matrix || !rotation_matrix || !transformed_matrix || !result)
		return (NULL);
	free_grid(tuple_matrix);
	free_grid(rotation_matrix);
	free_grid(transformed_matrix);
	return (result);
}

double	*scale_tuple(double *tuple)
{
	double	**tuple_matrix;
	double	**scaling_matrix;
	double	**transformed_matrix;
	double	*result;

	tuple_matrix = tuple_to_matrix(tuple);
	scaling_matrix = scaling(tuple);
	transformed_matrix = matrix_multiply(scaling_matrix, tuple_matrix);
	result = matrix_to_tuple(transformed_matrix);
	if (!tuple_matrix || !scaling_matrix || !transformed_matrix || !result)
		return (NULL);
	free_grid(tuple_matrix);
	free_grid(scaling_matrix);
	free_grid(transformed_matrix);
	return (result);
}

double	*translate_tuple(double *tuple)
{
	double	**tuple_matrix;
	double	**translation_matrix;
	double	**transformed_matrix;
	double	*result;

	tuple_matrix = tuple_to_matrix(tuple);
	translation_matrix = translation(tuple);
	transformed_matrix = matrix_multiply(translation_matrix, tuple_matrix);
	result = matrix_to_tuple(transformed_matrix);
	if (!tuple_matrix || !translation_matrix || !transformed_matrix || !result)
		return (NULL);
	free_grid(tuple_matrix);
	free_grid(translation_matrix);
	free_grid(transformed_matrix);
	return (result);
}

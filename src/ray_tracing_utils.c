/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:21:43 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/19 15:42:00 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*add_tuple(double *tuple_1, double *tuple_2)
{
	double	*sum;

	sum = malloc (4 * sizeof(double));
	if (!sum)
		return (perror(MALL_ERR), NULL);
	sum[0] = tuple_2[0] + tuple_1[0];
	sum[1] = tuple_2[1] + tuple_1[1];
	sum[2] = tuple_2[2] + tuple_1[2];
	sum[3] = tuple_2[3] + tuple_1[3];
	return (sum);
}

double	*subtract_tuple(double *tuple_1, double *tuple_2)
{
	double	*remainder;

	remainder = malloc (4 * sizeof(double));
	if (! remainder)
		return (perror(MALL_ERR), NULL);
	remainder[0] = tuple_1[0] - tuple_2[0];
	remainder[1] = tuple_1[1] - tuple_2[1];
	remainder[2] = tuple_1[2] - tuple_2[2];
	remainder[3] = tuple_1[3] - tuple_2[3];
	return (remainder);
}

double	dot_product_tuple(double *tuple_1, double *tuple_2)
{
	double	result;

	if (!tuple_1 || !tuple_2)
		return (0);
	result = tuple_2[0] * tuple_1[0]
		+ tuple_2[1] * tuple_1[1]
		+ tuple_2[2] * tuple_1[2]
		+ tuple_2[3] * tuple_1[3];
	return (result);
}

double	*multiply_scalar(double *tuple, double scalar)
{
	double	*result;

	result = allocate_tuple(0, 0, 0, 0);
	if (!result)
		return (NULL);
	result[0] = tuple[0] * scalar;
	result[1] = tuple[1] * scalar;
	result[2] = tuple[2] * scalar;
	result[3] = 0;
	return (result);
}

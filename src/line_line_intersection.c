/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_line_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:03:30 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/16 21:51:42 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_co_planar(double *origin_1, double *origin_2,
	double *vector_1, double *vector_2)
{
	double		cooplanar;
	double		*subtract;
	double		*cross;

	cooplanar = 0;
	subtract = subtract_tuple(origin_2, origin_1);
	if (!subtract)
		return (2);
	cross = cross_product(vector_1, vector_2);
	if (!cross)
		return (2);
	cooplanar = dot_product_tuple(vector_1, vector_2);
	if (cooplanar == 0)
		return (1);
	else
		return (0);
}

double	get_prameter_ray(double *origin_1, double *oringin_2,
	double *vector_1, double *vector_2)
{
	double	par_1;
	double	*origin_subtract;
	double	*cross_1;
	double	*cross_2;
	double	numerator;

	origin_subtract = subtract_tuple(oringin_2, origin_1);
	cross_1 = cross_product(origin_subtract, vector_1);
	cross_2 = cross_product(vector_1, vector_2);
	numerator = dot_product_tuple(origin_subtract, cross_2);
	par_1 = numerator / pow(cross_2[0], 2)
		+ pow(cross_2[1], 2) + pow(cross_2[2], 2);
	free(origin_subtract);
	free(cross_1);
	free(cross_2);
	return (par_1);
}

double	*line_intersection_point(double *origin_1, double *oringin_2,
		double *vec_1, double *vec_2)
{
	double	par_1;
	double	cooplanar;
	double	*is_parallel;
	double	*point;
	double	*vector_scalar;

	is_parallel = 0;
	cooplanar = is_co_planar(origin_1, oringin_2, vec_1, vec_2);
	if (cooplanar == 0)
	{
		is_parallel = cross_product(vec_1, vec_2);
		if (is_parallel[0] == 0 && is_parallel[1] == 0 && is_parallel[2] == 0)
			return (NULL);
		free(is_parallel);
		par_1 = get_prameter_ray(origin_1, oringin_2, vec_1, vec_2);
		vector_scalar = allocate_tuple((vec_1[0] * par_1), (vec_1[1] * par_1),
				(vec_1[2] * par_1), (vec_1[3] * par_1));
		if (!vector_scalar)
			return (NULL);
		point = add_tuple(origin_1, vector_scalar);
		if (!point)
			return (NULL);
		return (free(vector_scalar), point);
	}
	return (NULL);
}

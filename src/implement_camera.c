/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:57:26 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/15 14:21:06 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	**get_idemtrx_view_translate(double *forward, 
	double *left, double *true_up)
{
	double	*negative;
	double	*forward_neg;
	double	**idemtrx;
	int		i;

	negative = allocate_tuple(-1, -1, -1, 0);
	forward_neg = multiply_tuple_tuple(forward, negative);
	idemtrx = identity_mtrx(4);
	i = -1;
	while (++i < 3)
		idemtrx[0][i] = left[i];
	i = -1;
	while (++i < 3)
		idemtrx[1][i] = true_up[i];
	i = -1;
	while (++i < 3)
		idemtrx[2][i] = forward_neg[i];
	free(negative);
	free(forward_neg);
	return (idemtrx);
}

double	**get_transform_mtrx_view_transform(double *from, double *forward,
	double *left, double *true_up)
{
	double	*negative;
	double	**idemtrx;
	double	*from_neg;
	double	**translate;
	double	**transform;

	negative = allocate_tuple(-1, -1, -1, 0);
	idemtrx = get_idemtrx_view_translate(forward, left, true_up);
	from_neg = multiply_tuple_tuple(from, negative);
	translate = translation(from_neg);
	transform = matrix_multiply(idemtrx, translate);
	free(negative);
	free_grid(idemtrx);
	free(from_neg);
	free_grid(translate);
	return (transform);
}

double	**view_transform(double *from, double *to, double *up)
{
	double	*forward;
	double	*left;
	double	*true_up;
	double	**transform;

	forward = subtract_tuple(to, from);
	normalize_vector(forward);
	normalize_vector(up);
	left = cross_product(forward, up);
	true_up = cross_product(left, forward);
	transform = get_transform_mtrx_view_transform(from, forward, left, true_up);
	free(forward);
	free(left);
	free(true_up);
	return (transform);
}

t_camera	*camera(double hsize, double vsize, double field_of_view)
{
	t_camera	*c;

	c = malloc(sizeof(t_camera));
	if (!c)
		return (NULL);
	c->hsize = hsize;
	c->vsize = vsize;
	c->field_of_view = field_of_view;
	c->transform = identity_mtrx(4);
	return (c);
}

void	pixel_size(t_camera *c)
{
	double	half_view;
	double	aspect;

	half_view = tan(c->field_of_view / 2);
	aspect = c->hsize / c->vsize;
	if (aspect >= 1)
	{
		c->half_width = half_view;
		c->half_height = half_view / aspect;
	}
	else
	{
		c->half_width = half_view * aspect;
		c->half_height = half_view;
	}
	c->pixel_size = (c->half_width * 2) / c->hsize;
}
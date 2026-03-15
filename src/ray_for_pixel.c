/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_for_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:06:52 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/15 14:21:26 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*get_point_w(t_camera *c, double px, double py)
{
	double	xoffset;
	double	yoffset;
	double	world_x;
	double	world_y;
	double	*point_w;

	xoffset = (px + 0.5) * c->pixel_size;
	yoffset = (py + 0.5) * c->pixel_size;
	world_x = c->half_width - xoffset;
	world_y = c->half_height - yoffset;
	point_w = allocate_tuple(world_x, world_y, -1, 1);
	return (point_w);
}

t_ray	*ray_for_pixel(t_camera *c, double px, double py)
{
	double	*point_w;
	double	*point;
	double	*pixel;
	t_ray	*r;

	r = malloc(sizeof(t_ray));
	if (!r)
		return (NULL);
	point_w = get_point_w(c, px, py);
	pixel = multiply_matrix_tuple(c->inverse, point_w);
	point = allocate_tuple(0, 0, 0, 1);
	r->ray_origin = multiply_matrix_tuple(c->inverse, point);
	r->ray_direction = subtract_tuple(pixel, r->ray_origin);
	normalize_vector(r->ray_direction);
	free(point_w);
	free(point);
	free(pixel);
	return (r);
}
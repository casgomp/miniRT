/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:28:46 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/11 14:39:09 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*color_at(t_world *world, t_ray ray)
{
	t_intersection	*xs;
	t_intersection	*hit;
	int				count;
	int				i;
	t_comps			*comps;
	double			*colord;

	xs = intersect_world(world, ray, &count);
	if (!xs)
		return (BLACK_PIXEL);

	hit = NULL;
	i = -1;
	while (++i < count)
	{
		if (xs[i].t > EPSILON && xs[i].obj)
		{
			hit = &xs[i];
			break ;
		}
	}
	colord = NULL;
	if (hit)
	{
		comps = prepare_computations(hit, ray);
		colord = shade_hit(world, comps);
	}
	//free function for freeing arrays
	free(xs);//free each intersection, then free list
	return (colord);
}

void	render_loop(t_data *data, t_world *w, t_camera *c)
{
	double			x;
	double			y;
	t_ray			*r;
	double			*colord;
	int				color;

	y = -1.0;
	while (++y < c->vsize)
	{
		x = -1.0;
		while (++x < c->hsize)
		{
			r = ray_for_pixel(c, x, y);

			colord = color_at(w, *r);
			color = color_to_int(colord);
			img_pix_put(&(data->img), x, y, color);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

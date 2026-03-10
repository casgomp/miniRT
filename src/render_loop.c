/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:28:46 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/10 09:11:36 by pecastro         ###   ########.fr       */
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
		if (xs[i].t > 0.0001)
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

	printf("hsize=%f vsize=%f pixel_size=%f\n", c->hsize, c->vsize, c->pixel_size);
    printf("half_width=%f half_height=%f\n", c->half_width, c->half_height);

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
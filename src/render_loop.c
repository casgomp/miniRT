/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:28:46 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/19 12:18:26 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	check_if_hit_tval(t_world *world, t_ray *r, int *count, double distance)
{
	t_intersection	*xs;
	t_intersection	*hit;

	xs = intersect_world(world, *r, count);
	hit = check_if_hit(xs, count);
	free(r->ray_direction);
	free(r);
	if (hit && hit->t < distance)
		return (free(xs), true);
	else
		return (free(xs), false);
}

t_intersection	*check_if_hit(t_intersection *xs, int *count)
{
	t_intersection	*hit;
	int				i;

	hit = NULL;
	i = -1;
	while (++i < *count)
	{
		if (xs[i].t > EPSILON && xs[i].obj)
		{
			hit = &xs[i];
			break ;
		}
	}
	return (hit);
}

double	*hit_comps_color(t_world *world, t_ray ray, t_intersection *hit)
{
	double			*colord;
	t_comps			*comps;

	comps = NULL;
	colord = NULL;
	comps = prepare_computations(hit, ray);
	colord = shade_hit(world, comps);
	if (comps)
	{
		free(comps->point);
		free(comps->eyev);
		free(comps->normalv);
		free(comps);
	}
	return (colord);
}

double	*color_at(t_world *world, t_ray ray)
{
	t_intersection	*xs;
	t_intersection	*hit;
	int				count;
	double			*colord;

	colord = NULL;
	xs = intersect_world(world, ray, &count);
	if (!xs)
		return (BLACK_PIXEL);
	hit = check_if_hit(xs, &count);
	if (hit)
		colord = hit_comps_color(world, ray, hit);
	free(xs);
	return (colord);
}

void	render_loop(t_data *data, t_world *scene)
{
	double			x;
	double			y;
	t_ray			*r;
	double			*colord;
	int				color;

	y = -1.0;
	while (++y < scene->camera->vsize)
	{
		x = -1.0;
		while (++x < scene->camera->hsize)
		{
			r = ray_for_pixel(scene->camera, x, y);
			colord = color_at(scene, *r);
			color = color_to_int(colord);
			free(r->ray_direction);
			free(r->ray_origin);
			free(r);
			free(colord);
			img_pix_put(&(data->img), x, y, color);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
}

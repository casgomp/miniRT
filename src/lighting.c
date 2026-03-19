/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:25:57 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/19 14:50:43 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*get_ambient_color(t_world *world, t_comps *comps)
{
	double	*color;
	double	*old_color;

	color = multiply_tuple_tuple(comps->obj->material->color,
			world->ambient->rgb);
	old_color = color;
	color = multiply_scalar(color,
			comps->obj->material->ambient * world->ambient->intensity[0]);
	free(old_color);
	return (color);
}

bool	is_shadowed(t_world *world, double *point, t_light *light)
{
	double			*vector;
	double			distance;
	int				count;
	t_ray			*r;

	r = malloc(sizeof(t_ray));
	if (!r)
		return (NULL);
	vector = subtract_tuple(light->position, point);
	distance = get_vector_magnitude(vector);
	r->ray_origin = point;
	r->ray_direction = vector;
	vector = NULL;
	normalize_vector(r->ray_direction);
	return (check_if_hit_tval(world, r, &count, distance));
}

double	*shade_hit(t_world *world, t_comps *comps)
{
	bool	in_shadow;
	double	*tmp;
	double	*color;
	double	*old_color;
	t_light	*current_light;

	color = NULL;
	old_color = NULL;
	if (world->ambient)
		color = get_ambient_color(world, comps);
	else
		color = allocate_tuple(0, 0, 0, 0);
	current_light = world->light;
	while (current_light)
	{
		in_shadow = is_shadowed(world, comps->point, current_light);
		tmp = lighting(comps, current_light, in_shadow);
		old_color = color;
		color = add_tuple(color, tmp);
		free(old_color);
		free(tmp);
		current_light = current_light->next;
	}
	return (color);
}

double	*reflect(double *in, double *w_normal)
{
	double	scalar;
	double	*vector;
	double	*reflectv;

	scalar = 2 * dot_product_tuple(in, w_normal);
	vector = multiply_scalar(w_normal, scalar);
	reflectv = subtract_tuple(in, vector);
	free(vector);
	return (reflectv);
}

double	*lighting(t_comps *comps, t_light *light, bool in_shadow)
{
	double	*effective_color;
	double	*lightv;
	double	*diffuse;
	double	*specular;
	double	light_dot_normal;

	diffuse = NULL;
	specular = NULL;
	effective_color = get_effective_color(light, comps);
	if (in_shadow)
		return (get_ambient(effective_color, comps));
	lightv = subtract_tuple(light->position, comps->point);
	normalize_vector(lightv);
	light_dot_normal = dot_product_tuple(lightv, comps->normalv);
	if (light_dot_normal < 0)
		zeroed_diffuse_specular(&diffuse, &specular);
	else
	{
		diffuse = multiply_scalar(effective_color, 
				comps->obj->material->diffuse * light_dot_normal);
		find_specular(light, comps, lightv, &specular);
	}
	return (free(lightv), 
		get_result_color(diffuse, specular, effective_color, comps));
}

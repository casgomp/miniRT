/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:25:57 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/13 14:30:33 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*shade_hit(t_world *world, t_comps *comps)
{
		bool	in_shadow;
		double	*tmp;
		double	*color;
		double	*old_color;
		t_light	*current_light;
		
		in_shadow = false;
		color = NULL;
		old_color = NULL;
		if (world->ambient)
		{
			color = multiply_tuple_tuple(comps->obj->material->color, world->ambient->rgb);//material color, world ambient rgb
			old_color = color;
			color = multiply_scalar(color, comps->obj->material->ambient * world->ambient->intensity[0]);//mult scalar color, material ambient * world ambient intensity
			free(old_color);
			old_color = NULL;
		}
		else
			color = allocate_tuple(0,0,0,0);
		current_light = world->light;
		while (current_light)
		{
			tmp = lighting(comps->obj->material, current_light, 
		comps->point, comps->eyev, comps->normalv, in_shadow);
			old_color = color;
			color = add_tuple(color, tmp);
			free(old_color);
			current_light = current_light->next;
		}
		return (color);

		//test ch.8
		/* bool	in_shadow = true;
		return (lighting(comps->obj->material, world->light, 
		comps->point, allocate_tuple(0,0,-1,0), allocate_tuple(0,0,-1,0), in_shadow)); */
}
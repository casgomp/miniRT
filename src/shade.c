/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:25:57 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/11 20:08:31 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*shade_hit(t_world *world, t_comps *comps)
{
		bool	in_shadow = false;
		return (lighting(comps->obj->material, world->light, 
		comps->point, comps->eyev, comps->normalv, in_shadow));

		//test ch.8
		/* bool	in_shadow = true;
		return (lighting(comps->obj->material, world->light, 
		comps->point, allocate_tuple(0,0,-1,0), allocate_tuple(0,0,-1,0), in_shadow)); */
}
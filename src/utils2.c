/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:52:57 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/19 15:42:57 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*lstlast(t_object *lst)
{
	t_object	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while ((tmp -> next) != NULL)
		tmp = tmp -> next;
	return (tmp);
}

t_material	*init_material(double *color, double ambient
		, double specular, double shininess)
{
	t_material	*m;

	m = malloc(sizeof(t_material));
	if (!m)
		return (NULL);
	m->color = color;
	m->ambient = ambient;
	m->diffuse = 0.7;
	m->specular = specular;
	m->shininess = shininess;
	return (m);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:05:59 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/10 13:07:28 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_light	*allocate_ambient(char **identifier, int id)
{
	t_light		*ambient;

	ambient = ft_calloc(1, sizeof(t_light));
	if (!ambient)
		return (perror(MALL_ERR), NULL);
	ambient->id = id;
	ambient->type = AMBIENT_LIGHT;
	ambient->intensity = ft_atof(identifier[1]);
	ambient->rgb = str_to_rgb(identifier[2], 0);
	if (!ambient->rgb)
		return (free(ambient), NULL);
	ambient->next = NULL;
	return (ambient);
}

static t_light	*append_light_lst(t_world **scene, t_light *new)
{
	t_light	*tmp;

	if (!new)
		return ((*scene)->light);
	if (!(*scene)->light)
	{
		(*scene)->light = new;
		return ((*scene)->light);
	}
	tmp = (*scene)->light;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ((*scene)->light);
}

int	parse_ambient(char **data, t_world **scene, int id)
{
	double		value;
	char		*err_msg_1;
	char		*err_msg_2;
	t_light		*new;

	err_msg_1 = "ambient light value out of range ""0 <= vlaue <= 1"" \n";
	err_msg_2 = "ambient light prams misconfigured <intensity> <RGB vlaue>\n";
	if (ft_lst_strsize(data) != 3)
		return (print_error(2, err_msg_2));
	if (!ft_isnumber(data[1]))
		return (print_error(2, "ambient value is not a number\n"));
	value = ft_atof(data[1]);
	if (value < 0.0 || value > 1.0)
		return (print_error(2, err_msg_1));
	if (!rgb_parse(data[2]))
		return (0);
	new = allocate_ambient(data, id);
	(*scene)->light = append_light_lst(scene, new);
	return (1);
}

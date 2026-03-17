/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:52:21 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/17 20:38:33 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	check_light_pos(char *data)
{
	char	**cam_pos;
	char	*err_msg;
	int		i;

	i = 0;
	err_msg = "Light position misconfigured <x, y, z>\n";
	cam_pos = ft_split(data, ',');
	if (!cam_pos)
		return (perror(MALL_ERR), 0);
	if (ft_lst_strsize(cam_pos) != 3)
		return (print_error(2, err_msg));
	while (cam_pos[i])
	{
		if (ft_isnumber(cam_pos[i]))
			i ++;
		else
			return (ft_free_array(&cam_pos), print_error(2, err_msg));
	}
	ft_free_array(&cam_pos);
	return (1);
}

static t_light	*allocate_light(char **identifier, int i)
{
	t_light		*light;
	double		*light_pos;
	double		*rgb;

	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (perror(MALL_ERR), NULL);
	light_pos = str_to_double(identifier[1], 1);
	rgb = str_to_rgb(identifier[3], 0);
	if (!light_pos || !rgb)
		return (NULL);
	light->id = i;
	light->intensity = allocate_tuple(ft_atof(identifier[2]),
			ft_atof(identifier[2]), ft_atof(identifier[2]), 0);
	light->position = light_pos;
	light->rgb = rgb;
	light->type = LIGHT;
	light->next = NULL;
	return (light);
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

int	parse_light(char **data, t_world **scene, int id)
{
	char		*err_msg;
	t_light		*new;

	err_msg = "Light args misconfigured ex:\
<position: x,y,z> <intensity [0.0 to 1.0]>\
<RGB values ex: <255,255,255>\n";
	if (ft_lst_strsize(data) != 4)
		return (print_error(2, err_msg));
	if (!check_light_pos(data[1]))
		return (0);
	if (!ft_isnumber(data[2]))
		return (print_error(2, "Light vlaue is not a number\n"));
	if (ft_atof(data[2]) < 0.0 || ft_atof(data[2]) > 1.0)
		return (print_error(2, "Light intensity out of range\n"));
	if (!rgb_parse(data[3]))
		return (0);
	new = allocate_light(data, id);
	(*scene)->light = append_light_lst(scene, new);
	return (1);
}

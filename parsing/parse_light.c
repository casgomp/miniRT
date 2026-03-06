/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:52:21 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/06 14:51:36 by aabdella         ###   ########.fr       */
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

static t_object	*allocate_light(char **identifier, int i)
{
	t_object	*obj;
	double		*light_pos;
	int			*rgb;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (perror(MALL_ERR), NULL);
	light_pos = str_to_double(identifier[1], 1);
	rgb = str_to_int(identifier[3], 0);
	if (!light_pos || !rgb)
		return (NULL);
	obj->angle = 0;
	obj->brightness = ft_atof(identifier[2]);
	obj->object_id = i;
	obj->object_type = LIGHT;
	obj->rgb = rgb;
	obj->transform = translation(light_pos);
	if (!obj->transform)
		return (free(light_pos), free(rgb), NULL);
	obj->inverse = inverse(obj->transform, 4);
	obj->next = NULL;
	return (free(light_pos), obj);
}

int	parse_light(char **data, t_object **lst, int id)
{
	char		*err_msg;
	t_object	*new;

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
	*lst = append_object_lst(lst, new);
	return (1);
}

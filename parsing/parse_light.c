/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:52:21 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/04 20:33:37 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	rgb_parse(char *rgb)
{
	char		**rgb_values;
	char		*err_msg;
	int			i;

	i = 0;
	rgb_values = ft_split(rgb, ',');
	if (!rgb_values)
		return (perror(MALL_ERR), 0);
	err_msg = "RGB format misconfigured ex: ""255,255,255""\n";
	if (ft_lst_strsize(rgb_values) != 3)
		return (print_error(2, err_msg));
	while (rgb_values[i])
	{
		if (!ft_isnumber(rgb_values[i]))
			return (ft_free_array(&rgb_values),
				print_error(2, "RGB value is not a number\n"));
		if (ft_atoi(rgb_values[i]) < 0 || ft_atoi(rgb_values[i]) > 255)
			return (ft_free_array(&rgb_values),
				print_error(2, "RGB out of range (0-255)\n"));
		i++;
	}
	return (ft_free_array(&rgb_values), 1);
}

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

int	parse_light(char **data)
{
	char	*err_msg;

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
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:06:17 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/04 20:46:49 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_normal_vec(char *vec_str)
{
	char	**coordinates;
	double	magnitude;
	int		i;

	i = 0;
	coordinates = ft_split(vec_str, ',');
	if (!coordinates)
		return (perror(MALL_ERR), 0);
	if (ft_lst_strsize(coordinates) != 3)
		return (print_error(2, "plane dir misconfigured ex: <0.0, 0.0, 1.0>\n"));
	while (coordinates[i])
	{
		if (ft_isnumber(coordinates[i]))
			i ++;
		else
			return (ft_free_array(&coordinates),
				print_error(2, "vector vlaue is not a number""\n"));
	}
	magnitude = sqrt(powf(ft_atof(coordinates[0]), 2)
			+ powf(ft_atof(coordinates[1]), 2)
			+ powf(ft_atof(coordinates[2]), 2));
	if (magnitude > 1)
		return (ft_free_array(&coordinates)
			, print_error(2, "vecotor is not normaliszed\n"));
	return (ft_free_array(&coordinates), 1);
}

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

static int	plane_pos(char *data)
{
	char	**plane_pos;
	char	*err_msg;
	int		i;

	i = 0;
	err_msg = "plane point args misconfigured <x, y, z>\n";
	plane_pos = ft_split(data, ',');
	if (!plane_pos)
		return (perror(MALL_ERR), 0);
	if (ft_lst_strsize(plane_pos) != 3)
		return (print_error(2, err_msg));
	while (plane_pos[i])
	{
		if (ft_isnumber(plane_pos[i]))
			i ++;
		else
			return (ft_free_array(&plane_pos), print_error(2, err_msg));
	}
	ft_free_array(&plane_pos);
	return (1);
}

int	parse_plane(char **data)
{
	char	*err_msg;

	err_msg = "plane args misconfigured ex:\
<position: x,y,z> <normal vector ex:[0.0,0.0,1.0]>\
<RGB values ex: <255,255,255>\n";
	if (ft_lst_strsize(data) != 4)
		return (print_error(2, err_msg));
	if (plane_pos(data[1]) && is_normal_vec(data[2]) && rgb_parse(data[3]))
		return (1);
	else
		return (0);
}

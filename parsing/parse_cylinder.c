/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:26:02 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/02 20:46:22 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_normal_vec(char *vec_str)
{
	char	**coordinates;
	char	*err_msg;
	char	*err_msg_2;
	int		i;

	i = 0;
	coordinates = ft_split(vec_str, ',');
	err_msg = "Cylinder axis misconfigured ex: <0.0, 0.0, 1.0>\n";
	err_msg_2 = "vecotor is not normaliszed\n";
	if (!coordinates)
		return (perror(MALL_ERR), 0);
	if (ft_lst_strsize(coordinates) != 3)
		return (print_error(2, err_msg));
	while (coordinates[i])
	{
		if (ft_isnumber(coordinates[i]))
		{
			if (ft_atof(coordinates[i]) < -1.0 || ft_atof(coordinates[i]) > 1.0)
				return (ft_free_array(&coordinates), print_error(2, err_msg_2));
			else
				i ++;
		}
		else
			return (ft_free_array(&coordinates),
				print_error(2, "vector vlaue is not a number""\n"));
	}
	ft_free_array(&coordinates);
	return (1);
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
		if (ft_isnumber(rgb_values[i]))
		{
			if (ft_atoi(rgb_values[i]) > 255 || ft_atoi(rgb_values[i]) < 0)
				return (ft_free_array(&rgb_values),
					print_error(2, "RGB out of range ""0 to 255""\n"));
			else
				i ++;
		}
		else
			return (ft_free_array(&rgb_values),
				print_error(2, "RGB vlaue is not a number""\n"));
	}
	ft_free_array(&rgb_values);
	return (1);
}

static int	cylinder_base(char *data)
{
	char	**plane_pos;
	char	*err_msg;
	int		i;

	i = 0;
	err_msg = "Cylinder center point args misconfigured <x, y, z>\n";
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

int	parse_cylinder(char **data)
{
	char	*err_msg;

	err_msg = "cylinder args misconfigured ex:\
<position: x,y,z> <normal vector ex:[0.0,0.0,1.0]>\
<diameter> <Height> <RGB values ex: <255,255,255>\n";
	if (ft_lst_strsize(data) != 6)
		return (print_error(2, err_msg));
	if (!cylinder_base(data[1]) || !is_normal_vec(data[2]))
		return (0);
	if (ft_isnumber(data[3]) && ft_isnumber(data[4]))
	{
		if (ft_atof(data[3]) < 0.0 || ft_atof(data[4]) < 0.0)
			return (print_error(2, "raduis and height must be positive\n"));
	}
	else
		return (print_error(2, "raduis or height are not numbers\n"));
	if (!rgb_parse(data[5]))
		return (0);
	return (1);
}

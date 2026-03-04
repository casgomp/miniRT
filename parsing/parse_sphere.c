/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:06:53 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/04 20:34:01 by aabdella         ###   ########.fr       */
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

static int	check_sphere_pos(char *data)
{
	char	**sphere_pos;
	char	*err_msg;
	int		i;

	i = 0;
	err_msg = "sphere position misconfigured <x, y, z>\n";
	sphere_pos = ft_split(data, ',');
	if (!sphere_pos)
		return (perror(MALL_ERR), 0);
	if (ft_lst_strsize(sphere_pos) != 3)
		return (print_error(2, err_msg));
	while (sphere_pos[i])
	{
		if (ft_isnumber(sphere_pos[i]))
			i ++;
		else
			return (ft_free_array(&sphere_pos), print_error(2, err_msg));
	}
	ft_free_array(&sphere_pos);
	return (1);
}

int	parse_sphere(char **data)
{
	char	*err_msg;

	err_msg = "Sphere args misconfigured ex:\
<position: x,y,z> <raduis [0.0 to 1.0]>\
<RGB values ex: <255,255,255>\n";
	if (ft_lst_strsize(data) != 4)
		return (print_error(2, err_msg));
	if (!check_sphere_pos(data[1]))
		return (0);
	if (!ft_isnumber(data[2]))
		return (print_error(2, "Raduis vlaue is not a number\n"));
	if (!rgb_parse(data[3]))
		return (0);
	return (1);
}

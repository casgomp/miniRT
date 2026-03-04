/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:48:07 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/04 20:43:57 by aabdella         ###   ########.fr       */
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
		return (print_error(2, "cam dir misconfigured ex: <0.0, 0.0, 1.0>\n"));
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

static int	check_cam_pos(char *data)
{
	char	**cam_pos;
	char	*err_msg;
	int		i;

	i = 0;
	err_msg = "cam position misconfigured <x, y, z>\n";
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

int	parse_camera(char **data)
{
	char	*err_msg;

	err_msg = "Camer args misconfigured ex:\
<position: x,y,z> <normal vector: 0.0, 0.0, 1.0>\
<field of view: [0, 180]>\n";
	if (ft_lst_strsize(data) != 4)
		return (print_error(2, err_msg));
	if (!check_cam_pos(data[1]) || !is_normal_vec(data[2]))
		return (0);
	if (!ft_isnumber(data[3]))
		return (print_error(2, "fiels of view is not a number\n"));
	if (ft_atof(data[3]) < 0.0 || ft_atof(data[3]) > 180.0)
		return (print_error(2, "field of view out of range\n"));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:48:07 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/02 20:11:49 by aabdella         ###   ########.fr       */
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
	err_msg = "cam direction misconfigured ex: <0.0, 0.0, 1.0>\n";
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:48:07 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/06 14:27:31 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

static double	**transform_cam(char *identifier_1, char *identifier_2)
{
	double	*cam_pos;
	double	**translate;
	double	**transform_matrix;

	cam_pos = str_to_double(identifier_1, 1);
	if (!cam_pos)
		return (NULL);
	translate = translation(cam_pos);
	if (!translate)
		return (free(cam_pos), NULL);
	transform_matrix = align_to_vec(identifier_2, translate);
	if (!transform_matrix)
		return (free(cam_pos), free_grid(translate), NULL);
	return (free(cam_pos), free_grid(translate), transform_matrix);
}

t_object	*allocate_camera(char **identifier, int id)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (perror(MALL_ERR), NULL);
	obj->rgb = NULL;
	obj->object_id = id;
	obj->object_type = CAMERA;
	obj->brightness = 0;
	obj->transform = transform_cam(identifier[1], identifier[2]);
	obj->angle = ft_atof(identifier[3]);
	obj->inverse = inverse(obj->transform, 4);
	obj->next = NULL;
	return (obj);
}

int	parse_camera(char **data, t_object **lst, int id)
{
	char		*err_msg;
	t_object	*new;

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
	new = allocate_camera(data, id);
	*lst = append_object_lst(lst, new);
	return (1);
}

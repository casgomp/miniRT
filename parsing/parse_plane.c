/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:06:17 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/12 16:14:09 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
		if (!ft_isnumber(plane_pos[i]))
			return (ft_free_array(&plane_pos), print_error(2, err_msg));
		i ++;
	}
	return (ft_free_array(&plane_pos), 1);
}

static double	**plane_transform(char *identifier_1, char *indentifier_2)
{
	double		*pl_poistion;
	double		**translate;
	double		**transform_matrix;

	pl_poistion = str_to_double(identifier_1, 1);
	if (!pl_poistion)
		return (NULL);
	translate = translation(pl_poistion);
	if (!translate)
		return (free(pl_poistion), NULL);
	transform_matrix = align_to_vec(indentifier_2, translate);
	if (!transform_matrix)
		return (free(pl_poistion), free_grid(translate), NULL);
	return (free(pl_poistion), free_grid(translate), transform_matrix);
}

static t_object	*allocate_plane(char **indentifier, int id)
{
	t_object	*obj;
	double		*rgb;

	rgb = str_to_rgb(indentifier[3], 0);
	if (!rgb)
		return (NULL);
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (free(rgb), NULL);
	obj->angle = 0;
	obj->brightness = 0;
	obj->transform = plane_transform(indentifier[1], indentifier[2]);
	if (!obj->transform)
		return (free(rgb), free(obj), NULL);
	obj->inverse = inverse(obj->transform, 4);
	obj->object_type = PLANE;
	obj->object_id = id;
	obj->rgb = rgb;
	//obj->material = init_material(rgb, 0.0, 0.0, 0.1);
	obj->material = init_material(rgb, 0.1, 0.7, 200.0);
	obj->scale = NULL;
	obj->next = NULL;
	return (obj);
}

static t_object	*append_object_lst(t_world **scene, t_object *new)
{
	t_object	*tmp;

	if (!new)
		return ((*scene)->object);
	if (!(*scene)->object)
	{
		(*scene)->object = new;
		return ((*scene)->object);
	}
	tmp = (*scene)->object;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ((*scene)->object);
}

int	parse_plane(char **data, t_world **scene, int id)
{
	char		*err_msg;
	t_object	*new;

	err_msg = "plane args misconfigured ex:\
<position: x,y,z> <normal vector ex:[0.0,0.0,1.0]>\
<RGB values ex: <255,255,255>\n";
	if (ft_lst_strsize(data) != 4)
		return (print_error(2, err_msg));
	if (!plane_pos(data[1]) || !is_normal_vec(data[2]) || !rgb_parse(data[3]))
		return (0);
	new = allocate_plane(data, id);
	(*scene)->object = append_object_lst(scene, new);
	return (1);
}

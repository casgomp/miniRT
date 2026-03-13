/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:26:02 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/13 21:07:16 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

static double	**cylinder_transform(char *pos_id,
								char *dir_id,
								char *radius_id,
								char *height_id)
{
	double *pos;
	double **scale;
	double **rotate;
	double **translate;
	double **tmp;
	double **transform;

	pos = str_to_double(pos_id, 1);
	if (!pos)
		return (NULL);
	scale = identity_mtrx(4);
	scale[0][0] = ft_atof(radius_id);
	scale[1][1] = ft_atof(height_id) / 2.0;
	scale[2][2] = ft_atof(radius_id);
	rotate = align_to_vec(dir_id, identity_mtrx(4));
	translate = translation(pos);
	tmp = matrix_multiply(rotate, scale);
	transform = matrix_multiply(translate, tmp);
	return (free_grid(scale), free_grid(rotate), free_grid(translate)
		, free_grid(tmp), free(pos), transform);
}

static t_object	*allocate_cylinder(char **identifier, int id)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->transform = cylinder_transform(identifier[1], identifier[2],
			identifier[3], identifier[4]);
	obj->inverse = inverse(obj->transform, 4);
	obj->object_type = CYLINDER;
	obj->object_id = id;
	obj->scale = allocate_tuple(ft_atof(identifier[3]),
			ft_atof(identifier[4]), ft_atof(identifier[3]), 1);
	obj->next = NULL;
	obj->rgb = str_to_rgb(identifier[5], 0);
	if (!obj->rgb || !obj->scale)
		return (NULL);
	obj->material = init_material(obj->rgb, 0.1, 0.7, 200.0);
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

int	parse_cylinder(char **data, t_world **scene, int id)
{
	char		*err_msg;
	t_object	*new;

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
	new = allocate_cylinder(data, id);
	(*scene)->object = append_object_lst(scene, new);
	return (1);
}

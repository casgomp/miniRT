/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:26:02 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/06 16:20:29 by aabdella         ###   ########.fr       */
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

static double	**cylinder_transform(char *identifier_1, char *identifier_2
			, char *identifier_3, char *identifier_4)
{
	double		*pos;
	double		**scale;
	double		**translate;
	double		**transform;
	double		**rotate;

	pos = str_to_double(identifier_1, 1);
	scale = identity_mtrx(4);
	if (!scale || !pos)
		return (free(pos), NULL);
	scale[0][0] = ft_atof(identifier_3);
	scale[1][1] = ft_atof(identifier_3);
	scale[2][2] = ft_atof(identifier_4);
	scale[3][3] = 1;
	translate = translation(pos);
	transform = matrix_multiply(translate, scale);
	if (!transform || !translate)
		return (free_grid(scale), free_grid(translate), free(pos), NULL);
	rotate = align_to_vec(identifier_2, transform);
	if (!rotate)
		return (free_grid(scale), free_grid(translate),
			free_grid(transform), free(pos), NULL);
	return (free_grid(scale), free_grid(translate),
		free_grid(transform), free(pos), rotate);
}

t_object	*allocate_cylinder(char **identifier, int id)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->angle = 0;
	obj->brightness = 0;
	obj->transform = cylinder_transform(identifier[1], identifier[2],
			identifier[3], identifier[4]);
	obj->inverse = inverse(obj->transform, 4);
	obj->object_type = CYLINDER;
	obj->object_id = id;
	obj->next = NULL;
	obj->rgb = str_to_int(identifier[5], 0);
	if (!obj->rgb)
		return (NULL);
	return (obj);
}

int	parse_cylinder(char **data, t_object **lst, int id)
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
	*lst = append_object_lst(lst, new);
	return (1);
}

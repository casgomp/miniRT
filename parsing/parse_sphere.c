/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:06:53 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/07 17:40:30 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

static double	**transform_sphere(char *identifier_1, char *identifier_2)
{
	double		*sphere_center;
	double		**translate;
	double		**scale;
	double		**transform;
	double		*raduis;

	sphere_center = str_to_double(identifier_1, 1);
	raduis = malloc(4 * sizeof(double));
	if (!sphere_center || ! raduis)
		return (NULL);
	raduis[0] = ft_atof(identifier_2);
	raduis[1] = ft_atof(identifier_2);
	raduis[2] = ft_atof(identifier_2);
	raduis[3] = 1;
	translate = translation(sphere_center);
	scale = scaling(raduis);
	if (!translate || !scale)
		return (free(sphere_center), free(raduis), NULL);
	transform = matrix_multiply(translate, scale);
	if (!transform)
		return (free(sphere_center), free(raduis), free_grid(translate)
			, free_grid(scale), NULL);
	return (free(sphere_center), free(raduis), free_grid(translate)
		, free_grid(scale), transform);
}

static t_object	*allocate_sphere(char **identifier, int id)
{
	t_object	*obj;
	int			*rgb;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (NULL);
	rgb = str_to_int(identifier[3], 0);
	if (!rgb)
		return (free(obj), NULL);
	obj->object_id = id;
	obj->angle = 0;
	obj->brightness = 0;
	obj->scale = allocate_tuple(ft_atof(identifier[2]),
			ft_atof(identifier[2]), ft_atof(identifier[2]), 1);
	obj->transform = transform_sphere(identifier[1], identifier[2]);
	if (!obj->transform || !obj->scale)
		return (free(obj), free(rgb), NULL);
	obj->inverse = inverse(obj->transform, 4);
	obj->rgb = rgb;
	obj->object_type = SPHERE;
	obj->next = NULL;
	return (obj);
}

int	parse_sphere(char **data, t_object **lst, int id)
{
	char		*err_msg;
	t_object	*new;

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
	new = allocate_sphere(data, id);
	*lst = append_object_lst(lst, new);
	return (1);
}

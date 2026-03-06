/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 20:36:32 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/06 16:18:21 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_normal_vec(char *vec_str)
{
	char	**coordinates;
	double	magnitude;
	int		i;

	i = 0;
	coordinates = ft_split(vec_str, ',');
	if (!coordinates)
		return (perror(MALL_ERR), 0);
	if (ft_lst_strsize(coordinates) != 3)
		return (print_error(2, "vec dir misconfigured ex: <0.0, 0.0, 1.0>\n"));
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

int	rgb_parse(char *rgb)
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

double	**align_to_vec(char *identifier_2, double **matrix)
{
	double		**rotate_x;
	double		**rotate_y;
	double		**rotate_z;
	double		**x;
	double		**y;
	double		**z;
	double		*vec;

	vec = str_to_double(identifier_2, 0);
	if (!vec)
		return (NULL);
	x = rotation_x(acos(vec[0]));
	y = rotation_y(acos(vec[1]));
	z = rotation_z(acos(vec[2]));
	rotate_x = matrix_multiply(matrix, x);
	rotate_y = matrix_multiply(rotate_x, y);
	rotate_z = matrix_multiply(rotate_y, z);
	if (!rotate_x || !rotate_y || !rotate_z)
		return (free(vec), NULL);
	return (free(vec), free_grid(x), free_grid(y), free_grid(z)
		, free_grid(rotate_x), free_grid(rotate_y), rotate_z);
}

static const char	*object_type_to_string(t_OBJECT_TYP type)
{
	if (type == SPHERE)
		return ("SPHERE");
	else if (type == CYLINDER)
		return ("CYLINDER");
	else if (type == PLANE)
		return ("PLANE");
	else if (type == CAMERA)
		return ("CAMERA");
	else if (type == LIGHT)
		return ("LIGHT");
	else if (type == AMBIENT_LIGHT)
		return ("AMBIENT_LIGHT");
	return ("UNKNOWN");
}

void	print_object_list(t_object *lst)
{
	while (lst)
	{
		printf("--------------- OBJECT ---------------\n");
		printf("ID: %d\n", lst->object_id);
		printf("Type: %s\n", object_type_to_string(lst->object_type));
		printf("RGB: ");
		if (lst->rgb)
			printf("%d %d %d\n", lst->rgb[0], lst->rgb[1], lst->rgb[2]);
		else
			printf("(null)\n");
		printf("Brightness: %f\n", lst->brightness);
		printf("Angle: %f\n", lst->angle);
		printf("Transform matrix:\n");
		print_grid(lst->transform);
		printf("Inverse matrix:\n");
		print_grid(lst->inverse);
		printf("--------------------------------------\n\n");
		lst = lst->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 20:36:32 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/11 20:08:18 by pecastro         ###   ########.fr       */
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

double	***compute_rotation(char *identifier_2)
{
	double		**x;
	double		**y;
	double		**z;
	double		*vec;
	double		***rotation_fest;

	rotation_fest = malloc (3 * sizeof(double **));
	if (!rotation_fest)
		return (perror(MALL_ERR), NULL);
	vec = str_to_double(identifier_2, 0);
	if (!vec)
		return (free(rotation_fest), NULL);
	x = rotation_x(acos(vec[0]));
	y = rotation_y(acos(vec[1]));
	z = rotation_z(acos(vec[2]));
	if (!x || !y || !z)
		return (free(vec), free(rotation_fest), NULL);
	rotation_fest[0] = x;
	rotation_fest[1] = y;
	rotation_fest[2] = z;
	return (free(vec), rotation_fest);
}

double	**align_to_vec(char *identifier_2, double **matrix)
{
	double		**rotate_x;
	double		**rotate_y;
	double		**rotate_z;
	double		***rotation_fest;

	rotation_fest = compute_rotation(identifier_2);
	if (!rotation_fest)
		return (NULL);
	rotate_x = matrix_multiply(matrix, rotation_fest[0]);
	rotate_y = matrix_multiply(rotate_x, rotation_fest[1]);
	rotate_z = matrix_multiply(rotate_y, rotation_fest[2]);
	if (!rotate_x || !rotate_y || !rotate_z)
		return (NULL);
	return (free_grid(rotation_fest[0]), free_grid(rotation_fest[1])
		, free_grid(rotation_fest[2]), free_grid(rotate_x), free(rotation_fest)
		, free_grid(rotate_y), rotate_z);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 20:36:32 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/17 21:26:12 by aabdella         ###   ########.fr       */
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
	if (fabs(magnitude - 1.0) > EPSILON)
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

double	**compute_rotation(double *axis, double angle, double **matrix)
{
	double	**m;
	double	c;
	double	s;
	double	t;
	double	**result;

	normalize_vector(axis);
	c = cos(angle);
	s = sin(angle);
	t = 1 - c;
	m = identity_mtrx(4);
	if (!m)
		return (NULL);
	m[0][0] = t * axis[0] * axis[0] + c;
	m[0][1] = t * axis[0] * axis[1] - s * axis[2];
	m[0][2] = t * axis[0] * axis[2] + s * axis[1];
	m[1][0] = t * axis[0] * axis[1] + s * axis[2];
	m[1][1] = t * axis[1] * axis[1] + c;
	m[1][2] = t * axis[1] * axis[2] - s * axis[0];
	m[2][0] = t * axis[0] * axis[2] - s * axis[1];
	m[2][1] = t * axis[1] * axis[2] + s * axis[0];
	m[2][2] = t * axis[2] * axis[2] + c;
	result = matrix_multiply(matrix, m);
	return (free_grid(m), result);
}

double	**align_to_vec(char *identifier_2, double **matrix)
{
	double		*axis;
	double		*up;
	double		angle;
	double		*target;
	double		**rotation_fest;

	up = allocate_tuple(0, 1, 0, 0);
	target = str_to_double(identifier_2, 0);
	if (!up || ! target)
		return (NULL);
	if (fabs(dot_product_tuple(up, target)) > 1)
		return (matrix);
	axis = cross_product(up, target);
	angle = acos(dot_product_tuple(up, target));
	rotation_fest = compute_rotation(axis, angle, matrix);
	return (free(axis), free(up),
		free(target), rotation_fest);
}

t_object	*append_object_lst(t_world **scene, t_object *new)
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

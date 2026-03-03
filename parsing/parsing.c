/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:04:36 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/03 20:48:14 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	file_format_error(char *filename)
{
	int		len;

	if (!filename || filename[0] == '.')
	{
		write(2, "Error\nHidden files are not allowed\n", 35);
		return (0);
	}

	len = ft_strlen(filename);
	if (len < 3 || ft_strcmp(filename + len - 3, ".rt") != 0)
	{
		write(2, "Error\nfile format <filename>.rt\n", 32);
		return (0);
	}

	return (1);
}

double	*str_to_double(char *str, double i)
{
	double	*coordinates;
	char	**str_coordinates;

	coordinates = malloc(4 * sizeof(double));
	if (!coordinates)
		return (perror(MALL_ERR), NULL);
	str_coordinates = ft_split(str, ',');
	if (!str_coordinates)
		return (free(coordinates), perror(MALL_ERR), NULL);
	coordinates[0] = ft_atof(str_coordinates[0]);
	coordinates[1] = ft_atof(str_coordinates[1]);
	coordinates[2] = ft_atof(str_coordinates[2]);
	coordinates[3] = i;
	ft_free_array(str_coordinates);
	return (coordinates);
}

int	*str_to_int(char *str, int i)
{
	int		*coordinates;
	char	**str_coordinates;

	coordinates = malloc(4 * sizeof(int));
	if (!coordinates)
		return (perror(MALL_ERR), NULL);
	str_coordinates = ft_split(str, ',');
	if (!str_coordinates)
		return (free(coordinates), perror(MALL_ERR), NULL);
	coordinates[0] = ft_atoi(str_coordinates[0]);
	coordinates[1] = ft_atoi(str_coordinates[1]);
	coordinates[2] = ft_atoi(str_coordinates[2]);
	coordinates[3] = i;
	ft_free_array(str_coordinates);
	return (coordinates);
}

t_object	*allocate_ambient(char **identifier, int i)
{
	t_object	*obj;
	int			*rgb_vlaues;

	obj->object_id = i;
	obj->object_type = AMBIENT_LIGHT;
	obj->brightness = ft_atof(identifier[1]);
	obj->transform = NULL;
	obj->angle = 0;
	obj->rgb = str_to_int(identifier[2], 0);
	if (!obj->rgb)
		return (NULL);
	obj->inverse = NULL;
	obj->next = NULL;
	return (obj);
}


t_object	*allocate_camera(char **identifier, int i)
{
	t_object	*obj;
	double		*cam_pos;
	double		*cam_dir;
	double		*transform;
	double		**transfom_matrix;

	cam_pos = str_to_double(identifier[1], 1);
	cam_dir = str_to_double(identifier[2], 0);
	if (!cam_pos || !cam_dir)
		return (NULL);
	transform = cross_product(cam_pos, cam_dir);
	if (!transform)
		return (free(cam_pos), free(cam_dir), NULL);
	transfom_matrix = tuple_to_matrix(transform);
	if (!transfom_matrix)
		return (free(cam_pos), free(cam_dir), free(transform), NULL);
	obj->rgb = NULL;
	obj->object_id = i;
	obj->object_type = CAMERA;
	obj->brightness = 0;
	obj->transform = transfom_matrix;
	obj->angle = ft_atof(identifier[3]);
	obj->inverse = inverse(obj->transform, 4);
	obj->next = NULL;
	free(cam_pos);
	free(cam_dir);
	free(transform);
	return (obj);
}

t_object	*allocate_light(char **identifier, int i)
{
	t_object	*obj;
	double		*light_pos;
	int			*rgb;

	light_pos = str_to_double(identifier[1], 1);
	rgb = str_to_int(identifier[3], 0);
	if (!light_pos || !rgb)
		return (NULL);
	obj->angle = 0;
	obj->brightness = ft_atof(identifier[2]);
	obj->object_id =i;
	obj->object_type = LIGHT;
	obj->rgb = rgb;
	obj->transform = tuple_to_matrix(light_pos);
	if (!obj->transform)
		return (free(light_pos), NULL);
	obj->inverse = inverse(obj->transform, 4);
	obj->next = NULL;
	return (obj);
}

t_object	*allocate_plane(char **indentifier, int i)
{
	t_object	*obj;
	double		*pl_poistion;
	double		*pl_orientation;
	int			*rgb;
	double		*transform;
	double		**transform_matrix;

	pl_poistion = str_to_double(indentifier[1], 1);
	pl_orientation = str_to_double(indentifier[3], 0);
	rgb = str_to_int(indentifier[3], 0);
	if (!rgb || pl_orientation || pl_poistion)
		return (NULL);
	transform = cross_product(pl_poistion, pl_orientation);
	if (!transform)
		return (free(pl_orientation), free(pl_poistion), free(rgb), NULL);
	transform_matrix = tuple_to_matrix(transform);
	if (!transform_matrix)
		return (free(pl_orientation), free(pl_poistion), free(rgb)
			, free(transform),NULL);
	obj->angle = 0;
	obj->brightness = 0;
	obj->transform = transform_matrix;
	obj->inverse = inverse(obj->transform, 4);
	if (!obj->inverse)
		return (free(pl_orientation), free(pl_poistion), free(rgb)
			, free(transform), free_matrix(transform_matrix), NULL);
	obj->object_type = PLANE;
	obj->object_id = i;
	obj->rgb = rgb;
	obj->next = NULL;
	free(pl_poistion);
	free(pl_orientation);
	free(transform);
	return (obj);
}
t_object *append_object_lst(char **identifier_line, t_object **lst)
{
	t_object		*new_node;
	t_object		*tmp;

	new_node = allocte_oject_data(obj_id, t, ray);
	free (t);
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	if (*lst == NULL)
	{
		*lst = new_node;
		return (new_node);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (new_node);
}

int	identifier_check(char *identifier_line)
{
	char	*error_msg;
	char	**identifier_data;

	error_msg = "wrong or missing identifier\n";
	identifier_data = ft_split(identifier_line, ' ');
	if (!identifier_data)
		return (perror(MALL_ERR), 0);
	if (ft_strcmp(identifier_data[0], "A") == 0)
	{
		if (!parse_ambient(identifier_data))
			return (ft_free_array(&identifier_data), 0);
	}
	else if (ft_strcmp(identifier_data[0], "C") == 0)
	{
		if (!parse_camera(identifier_data))
			return (ft_free_array(&identifier_data), 0);
	}
	else if (ft_strcmp(identifier_data[0], "L") == 0)
	{
		if (!parse_light(identifier_data))
			return (ft_free_array(&identifier_data), 0);
	}
	else if (ft_strcmp(identifier_data[0], "sp") == 0)
	{
		if (!parse_sphere(identifier_data))
			return (ft_free_array(&identifier_data), 0);
	}
	else if (ft_strcmp(identifier_data[0], "pl") == 0)
	{
		if (!parse_plane(identifier_data))
			return (ft_free_array(&identifier_data), 0);
	}
	else if (ft_strcmp(identifier_data[0], "cy") == 0)
	{
		if (!parse_cylinder(identifier_data))
			return (ft_free_array(&identifier_data), 0);
	}
	else
	{
		write(2, "Error\n", 6);
		write(2, error_msg, ft_strlen(error_msg));
		return (0);
	}
	ft_free_array(&identifier_data);
	return (1);
}

int main (int argc, char **argv)
{
	if (argc > 2)
	{
		write(2, "Error\nenter one argument only\n", 30);
		return (1);
	}
	/*if(!file_format_error(argv[1]))
		return (1);*/
	if (!identifier_check(argv[1]))
		return (1);
	printf("all good\n");
}

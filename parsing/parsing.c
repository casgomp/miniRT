/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:04:36 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/04 22:22:00 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


/*t_object	*allocate_ambient(char **identifier, int i)
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

t_object	*allocate_sphere(char **identifier, int i)
{
	t_object	*obj;
	double		*sphere_center;
	double		**translate_matrix;
	double		**scale_matrix;
	double		**transform_matrix;
	double		*raduis;
	int			*rgb;

	sphere_center = str_to_double(identifier[1], 1);
	rgb = str_to_int(identifier[3], 0);
	raduis = malloc(4 *sizeof(double));
	if (!rgb || sphere_center || raduis)
		return (NULL);
	raduis[0] = ft_atof(identifier[2]);
	raduis[1] = ft_atof(identifier[2]);
	raduis[2] = ft_atof(identifier[2]);
	raduis[3] = 1;
	translate_matrix = tuple_to_matrix(sphere_center);
	scale_matrix = scaling(raduis);
	if (!translate_matrix || !scale_matrix)
		return (free(sphere_center), free(rgb), free(raduis), NULL);
	transform_matrix = matrix_multiply(transform_matrix, scale_matrix);
	if (!transform_matrix)
		return (free(sphere_center), free(rgb), free(raduis)
			, free_matrix(translate_matrix), free_matrix(scale_matrix), NULL);
	obj->object_id = i;
	obj->angle = 0;
	obj->brightness = 0;
	obj->transform = transform_matrix;
	obj->inverse = inverse(obj->transform, 4);
	obj->rgb = rgb;
	obj->object_type = SPHERE;
	obj->next = NULL;
	return (obj);
}

t_object	*allocate_cylinder(char **indentifier, int i)
{
	t_object	*obj;
	int			*rgb;
	double		*pos;
	double		*vec;
	double		**scale_matrix;
	double		**translate_matrix;
	double		**transform_matrix;
	double		**rotate_x;
	double		**rotate_y;
	double		**rotate_z;


	scale_matrix = identity_mtrx(4);
	vec = str_to_double(indentifier[2], 0);
	if (!scale_matrix || vec)
		return (NULL);
	scale_matrix[0][0] = ft_atof(indentifier[3]);
	scale_matrix[1][1] = ft_atof(indentifier[3]);
	scale_matrix[2][2] = ft_atof(indentifier[4]);
	scale_matrix[3][3] = 1;
	translate_matrix = tuple_to_matrix(str_to_double(indentifier[1], 1));
	transform_matrix = matrix_multiply(translate_matrix, scale_matrix);
	if (!transform_matrix || translate_matrix)
		return (free_arr(scale_matrix), free(vec), NULL);
	rotate_x = matrix_multiply(transform_matrix, rotation_x(acos(vec[0])));
	rotate_y = matrix_multiply(rotate_x, rotation_y(acos(vec[1])));
	rotate_z = matrix_multiply(rotate_y, rotation_z(acos(vec[2])));
	if (!rotate_x || !rotate_y || rotate_z)
		return (free_arr(scale_matrix), free(vec), free_matrix(transform_matrix)
			, free_matrix(translate_matrix) , NULL);
	transform_matrix = rotate_z;
	obj->angle = 0;
	obj->brightness = 0;
	obj->transform = transform_matrix;
	obj->inverse = inverse(transform_matrix, 4);
	obj->object_type = CYLINDER;
	obj->object_id = i;
	obj->next = NULL;
	obj->rgb = str_to_int(indentifier[5], 0);
	if (!obj->inverse || !obj->rgb)
		return (NULL);
	free(vec);
	free_matrix(scale_matrix);
	free_matrix(transform_matrix);
	free_matrix(translate_matrix);
	free_matrix(rotate_x);
	free_matrix(rotate_y);
	return (obj);
}*/


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

int	main(int argc, char **argv)
{
	char	**rd_lines;
	char	*line;
	char	*path;
	int		fd;
	int		i;

	if (argc != 2)
		return (write(2, "Error\nenter one argument only\n", 30), 1);
	if (!file_format_error(argv[1]))
		return (1);
	rd_lines = NULL;
	path = ft_strjoin("scene/", argv[1]);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	line = get_next_line(fd);
	while (line)
	{
		rd_lines = ft_append_str(rd_lines, line);
		line = get_next_line(fd);
	}
	close(fd);
	i = 0;
	while (rd_lines && rd_lines[i])
	{
		if (identifier_check(rd_lines[i]))
			return (free(path), ft_free_array(&rd_lines)
				, close(fd), free(line), 1);
		printf("%s", rd_lines[i]);
		i ++;

	}
	printf("all good\n");
	free(path);
	ft_free_array(&rd_lines);
	return (0);
}

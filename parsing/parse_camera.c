/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:48:07 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/16 18:34:28 by aabdella         ###   ########.fr       */
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
	double	*from;
	double	*dir;
	double	*up;
	double	*to;
	double	**transform;

	from = str_to_double(identifier_1, 1);
	dir = str_to_double(identifier_2, 1);
	up = allocate_tuple(0, 1, 0, 0);
	to = add_tuple(from, dir);
	transform = view_transform(from, to, up);
	return (free(from), free(dir), free(up), free(to), transform);
}

static t_camera	*allocate_camera(char **identifier, int id)
{
	t_camera	*cam;
	double		fov_degrees;

	cam = ft_calloc(1, sizeof(t_camera));
	if (!cam)
		return (perror(MALL_ERR), NULL);
	fov_degrees = ft_atof(identifier[3]);
	cam->field_of_view = fov_degrees * (PI / 180);
	cam->id = id;
	cam->hsize = WIN_W;
	cam->vsize = WIN_H;
	cam->type = CAMERA;
	cam->next = NULL;
	cam->transform = transform_cam(identifier[1], identifier[2]);
	cam->inverse = inverse(cam->transform, 4);
	if (!cam->inverse || !cam->transform)
		return (free(cam), NULL);
	pixel_size(cam);
	return (cam);
}

static t_camera	*append_cam_lst(t_world **scene, t_camera *new)
{
	t_camera	*tmp;

	if (!new)
		return ((*scene)->camera);
	if (!(*scene)->camera)
	{
		(*scene)->camera = new;
		return ((*scene)->camera);
	}
	tmp = (*scene)->camera;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ((*scene)->camera);
}

int	parse_camera(char **data, t_world **lst, int id)
{
	char		*err_msg;
	t_camera	*new;

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
	(*lst)->camera = append_cam_lst(lst, new);
	return (1);
}

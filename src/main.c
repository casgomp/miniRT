/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:20:33 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/09 19:26:01 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	grid_cpy(double **dst, double src[100][100], int size)
{
	int i = 0;
	int j = 0;

	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			dst[i][j] = src[i][j];
			j ++;
		}
		i ++;
	}
}


t_object	*init_obj(double **transform, t_OBJECT_TYP object_type, t_material *m)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->next = NULL;
    obj->transform = transform; //(always initilize to identity, then multiply by tranformations if there are)
	obj->inverse = inverse(obj->transform, 4);
	obj->object_type = object_type;
	obj->material = m;
	return (obj);
}

t_material	*init_material(double *color, double ambient, double specular, double shininess)//temporary util to initialize material (eventually done in parsing)
{
	t_material	*m;

	m = malloc(sizeof(t_material));
	if (!m)
		return (NULL);

	m->color = color;//what color?make sure w=0 always for colors.
	m->ambient = ambient;
	m->diffuse = 1.0;
	m->specular = specular;
	m->shininess = shininess;//necessary(yes)?where do we get this value from?;
	return (m);
}

/*int	main(int argc, char **argv)
{
	t_data		data;
	t_object	*lst;

	if (argc != 2)
		return (print_error(2, "only one arg allowed <file_name.rt\n"));
	if (!file_format_error(argv[1]))
		return (1);
	if (ft_minilibx_setup(&data))
		return (perror("minilibx_setup"), 1);
	lst = NULL;
	lst = parse_input(argv[1], lst);
	print_object_list(lst);

	t_light	*light;
	light = malloc(sizeof(t_light));
	if (!light)
		return (1);//and free data, etc?
	light->intensity = allocate_tuple(1,1,1,0);//this is just a color multiplier (so not a dot nor a vector)
	light->position = allocate_tuple(-10,10,-10,1);
	//initialize world
	t_world	*w = malloc(sizeof(t_world));
	if (!w)
		return (1);//and free data, materials, objects, etc...
	w->light = light;
	w->object = lst;

	//camera
	t_camera *c = camera(WIN_W,WIN_H,PI/3);
	if (!c)
		return (1);
	pixel_size(c);
	printf("pixel_size = %f\n", c->pixel_size);

	double	*from = allocate_tuple(0,1.5,-5,1);
	double	*to = allocate_tuple(0,1,0,1);
	double	*up = allocate_tuple(0,1,0,1);
	c->transform = view_transform(from, to, up);
	print_grid(c->transform);

	printf("Starting render\n");
	render_loop2(&data, w, c);
	printf("Render finished\n");

	mlx_loop(data.mlx_ptr);

	free(light->intensity);
	free(light->position);

    return (0);
}*/


int	ft_minilibx_setup(t_data *data)
{
	data->error_msg = NULL;
	data->exit_code = 0;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		terminate(data, 1, MLX_ERR);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, "miniRT");
	if (!data->win_ptr)
		terminate(data, 1, MLX_ERR);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	//mlx_loop_hook(data->mlx_ptr, &render, data); //use only for animations
	mlx_hook(data->win_ptr, 17, 0, handle_destroy_notify, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data);
	return (0);
}

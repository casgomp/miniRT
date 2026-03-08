/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:20:33 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/08 16:39:03 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*void	grid_cpy(double **dst, double src[100][100], int size)
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
}*/

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

t_material	*init_material(double *color, double ambient, double diffuse, double specular, double shininess)//temporary util to initialize material (eventually done in parsing)
{
	t_material	*m;

	m = malloc(sizeof(t_material));
	if (!m)
		return (NULL);
	m->color = color;//what color?make sure w=0 always for colors.
	m->ambient = ambient;
	m->diffuse = diffuse;
	m->specular = specular;
	m->shininess = shininess;//necessary(yes)?where do we get this value from?;
	return (m);
}

/*int main(int argc, char **argv) //main Ch.7
{
    t_data 		data;

	(void)argc;
	(void)argv;
    if (ft_minilibx_setup(&data))
		return (perror("minilibx_setup"), 1);

	//implementing view/camera

	t_camera *c = camera(WIN_W,WIN_H,PI/3);
	if (!c)
		return (1);
	pixel_size(c);
	printf("pixel_size = %f\n", c->pixel_size);

	double	*from = allocate_tuple(0,0,3,1);
	double	*to = allocate_tuple(0,0,0,1);
	double	*up = allocate_tuple(0,1,0,1);
	c->transform = view_transform(from, to, up);
	print_grid(c->transform);

	t_light	*light;
	light = malloc(sizeof(t_light));
	if (!light)
		return (1);//and free data, etc?
	light->intensity = allocate_tuple(1,1,1,0);//this is just a color multiplier (so not a dot nor a vector)
	light->position = allocate_tuple(200,5,-10,1);

	//initialize materials
	t_material *m1 = init_material(allocate_tuple(0.8,1.0,0.6,0), 0.1, 0.7, 0.2, 200.0);
	if (!m1)
		return (1); //and free data, etc...

	//initiliaze objects
	//obj1
	t_object	*obj1 = init_obj(identity_mtrx(4), SPHERE, m1);
	if (!obj1)
		return (1); //and free data, materials, etc...
	//obj2
	double	*scaling_vector = allocate_tuple(0.5,0.5,0.5,0);
	double	**scaling_matrix = scaling(scaling_vector);//0 for vector?

	double	**transform_obj2 = matrix_multiply(identity_mtrx(4), scaling_matrix);
	t_object	*obj2 = init_obj(transform_obj2, SPHERE, m1);//m1 here for testing?
	if (!obj2)
		return (1); //and free data, materials, etc...
	free(scaling_vector);
	free_grid(scaling_matrix);

	//create object list
	lstadd(&obj1, obj2);

	//initialize world
	t_world	*w = malloc(sizeof(t_world));
	if (!w)
		return (1);//and free data, materials, objects, etc...
	w->light = light;
	w->object = obj1;

    printf("Starting render\n");
	render_loop2(&data, w, c);
    printf("Render finished\n");

    mlx_loop(data.mlx_ptr);

	free(light->intensity);
	free(light->position);
	free(m1->color);
	free(obj1->material);
	free(obj1);

    return (0);
}//*/


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

t_material	*init_material(double *color, double ambient, double diffuse, double specular, double shininess)//temporary util to initialize material (eventually done in parsing)
{
	t_material	*m;

	m = malloc(sizeof(t_material));
	if (!m)
		return (NULL);
	m->color = color;//what color?make sure w=0 always for colors.
	m->ambient = ambient;
	m->diffuse = diffuse;
	m->specular = specular;
	m->shininess = shininess;//necessary(yes)?where do we get this value from?;
	return (m);
}

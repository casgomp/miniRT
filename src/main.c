/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:20:33 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/28 18:43:00 by pecastro         ###   ########.fr       */
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
/*
int	main(int argc, char **argv)
{
	t_data			data;
	t_matrix		matrix;
	double			*tuple;
	int				size;
	double			**grid_1;
	double			**grid_2;
	int				fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror(argv[1]), 1);
	//parse(fd);
	(void)argc;
	(void)argv;
	size = 3;
	double		test_grid_1[100][100] = {
									{88, 158, 72},
									{156, 293, 120},
									{151, 255, 132}

								};
	double		test_grid_2[100][100] = {
									{10, 16, 0},
									{1, 9, 12},
									{4, 3, 0}
								};
	grid_1 = allocate_grid(size);
	grid_2 = allocate_grid(size);
	grid_cpy(grid_1, test_grid_1, size);
	grid_cpy(grid_2, test_grid_2, size);
	tuple = allocate_tuple(5.5, 6.25, 3.33, 0);
	matrix = construct_matrix(grid_1);
	print_grid(matrix.grid);
	printf("\n %f\n", matrix.determinant);
	print_grid(matrix.transpose);
	printf("\n");
	print_grid(matrix.inverse);
	printf("\n");
	double **multi = matrix_multiply(grid_1, matrix.inverse);
	print_grid(multi);
	free_matrix(&matrix);
	free_grid(grid_1);
	free_grid(grid_2);
	free_grid(multi);
	double	angle = degrees_to_radians(90);
	double	*rotate;
	rotate = rotate_tuple_z(tuple, angle);
	printf("\n%f, %f, %f\n", rotate[0], rotate[1], rotate[2]);
	free(rotate);
	free(tuple);
	if (ft_minilibx_setup(&data))
		return (1);
	//create sphere
	t_sphere s;
	s.radius = 1;
	s.center = allocate_tuple(0,0,0,1);
	render_loop(&data, &s);
	mlx_loop(data.mlx_ptr);
	free(s.center);
	return (0);
}*/

/*//test window
int	main(int argc, char **argv)
{
    void *mlx;
    void *win;

	(void)argc;
	(void)argv;
    mlx = mlx_init();
    if (!mlx) {
        printf("MLX INIT FAILED\n");
        return (1);
    }
    win = mlx_new_window(mlx, 800, 800, "TEST");
    if (!win) {
        printf("WIN INIT FAILED\n");
        return (1);
    }
    printf("Window should be open. Press Ctrl+C to stop.\n");
    mlx_loop(mlx);
    return (0);
}*/

/*
int main(int argc, char **argv) //main Ch.5
{
    t_data data;

	(void)argc;
	(void)argv;
    if (ft_minilibx_setup(&data))
		return (perror("minilibx_setup"), 1);
	
    mlx_do_sync(data.mlx_ptr); //unnecessary? (forces the window to appear on some systems)

    t_sphere s;
    s.radius = 1;
    s.center = allocate_tuple(0,0,0,1);

    printf("Starting render\n");
    render_loop(&data, &s);
    printf("Render finished\n");

    mlx_loop(data.mlx_ptr);
    return (0);
}//*/

int main(int argc, char **argv) //main Ch.5 and Ch.6
{
    t_data 		data;
	t_object	*s;//eventually this would be world, a t_object linked list of all objects in the scene (i.e. in the world)

	(void)argc;
	(void)argv;
    if (ft_minilibx_setup(&data))
		return (perror("minilibx_setup"), 1);
    mlx_do_sync(data.mlx_ptr);//unnecessary? (used for debugging: forces the window to appear on some systems)

	/*//test reflectv (delete after)
	double	*in = allocate_tuple(0,-1,0,0);
	double	*w_normal = allocate_tuple(sqrt(2)/2,sqrt(2)/2,0,0);
	double	*reflectv = reflect(in, w_normal);
	printf("reflectv = %f,%f,%f,%f\n", reflectv[0],reflectv[1],reflectv[2],reflectv[3]);
	free(in); free(w_normal); free(reflectv);
	//*/
	
	//initialize light
	t_light	*light;
	light = malloc(sizeof(t_light));
	if (!light)
		return (1);//and free data, etc?
	light->intensity = allocate_tuple(1,1,1,0);//this is just a color multiplier (so not a dot nor a vector)
	light->position = allocate_tuple(-10,10,-10,1);

	//initialize material
	t_material	*m;
	m = malloc(sizeof(t_material));
	if (!m)
		return (1);//and free data, etc?
	m->color = allocate_tuple(1,0.2,1,0);//what color?make sure w=0 always for colors.
	m->ambient = 0.1;
	m->diffuse = 0.9;
	m->specular = 0.9;
	m->shininess = 200.0;//necessary?

	s = malloc(sizeof(t_object));
	if (!s)
		return (1);
	//initialize object:
	s->next = NULL;
    s->transform = identity_mtrx(4);//eventually in parser (always initilize to identity , then multiply by tranformations if there are)
	s->inverse = inverse(s->transform, 4);
	s->object_type = 1;
	s->material = m;

    printf("Starting render\n");
    render_loop2(&data, s, light);
    printf("Render finished\n");

    mlx_loop(data.mlx_ptr);
	
	free(light->intensity);
	free(light->position);
	free(m->color);
	free(s->material);
	free(s);

    return (0);
}//*/

/*
int	main(int argc, char **argv)
{
	t_sphere	s;
	double		*p;
	double		*normal;

	(void)argc;
	(void)argv;
	//eventually would pass world/scene instead of just one object
	s.radius = 1;
    s.center = allocate_tuple(0,0,0,1);
	if (!s.center)
		return (0);
	p = allocate_tuple(1,0,0,1);
	normal = lightshade_test(&s, p);
	free(s.center);
	free(p);
	printf("normal = %f,%f,%f\n", normal[0], normal[1], normal[2]);
	free(normal);
	return (1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:20:33 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/10 14:24:51 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	//grid_cpy(grid_1, test_grid_1, size);
	//grid_cpy(grid_2, test_grid_2, size);
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

/*
int main(int argc, char **argv) //main Ch.5 and Ch.6
{
    t_data 		data;
	t_object	*s;//eventually this would be world, a t_object linked list of all objects in the scene (i.e. in the world)

	(void)argc;
	(void)argv;
    if (ft_minilibx_setup(&data))
		return (perror("minilibx_setup"), 1);
    mlx_do_sync(data.mlx_ptr);//unnecessary? (used for debugging: forces the window to appear on some systems)

	//test reflectv (delete after)
	//double	*in = allocate_tuple(0,-1,0,0);
	//double	*w_normal = allocate_tuple(sqrt(2)/2,sqrt(2)/2,0,0);
	//double	*reflectv = reflect(in, w_normal);
	//printf("reflectv = %f,%f,%f,%f\n", reflectv[0],reflectv[1],reflectv[2],reflectv[3]);
	//free(in); free(w_normal); free(reflectv);

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
	m->shininess = 200.0;//necessary(yes)?where do we get this value from?

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


/* int main(int argc, char **argv) //main Ch.7
{
    t_data 		data;
	//t_object	*obj;//eventually this would be a t_object linked list of all objects in the scene
	//t_world		*w;//world includes all objects, lights, etc. probably also camera?

	(void)argc;
	(void)argv;
    if (ft_minilibx_setup(&data))
		return (perror("minilibx_setup"), 1); */

	//implementing view/camera

/* 	t_camera *c = camera(WIN_W,WIN_H,PI/3);
	if (!c)
		return (1);
	pixel_size(c);
	printf("pixel_size = %f\n", c->pixel_size);

	double	*from = allocate_tuple(0,0,3,1);
	double	*to = allocate_tuple(0,0,0,1);void	normalize_vector(double *vector)
	double	*up = allocate_tuple(0,1,0,1);
	c->transform = view_transform(from, to, up);
	print_grid(c->transform); */

	//initialize light
	/* t_light	*light;
	light = malloc(sizeof(t_light));
	if (!light)
		return (1);//and free data, etc?
	light->intensity = allocate_tuple(1,1,1,0);//this is just a color multiplier (so not a dot nor a vector)
	light->position = allocate_tuple(200,5,-10,1); */

	//initialize materials
	/* t_material *m1 = init_material(allocate_tuple(0.8,1.0,0.6,0), 0.1, 0.7, 0.2, 200.0);
	if (!m1)
		return (1); //and free data, etc...
 */
	//initiliaze objects
	//obj1
	/* t_object	*obj1 = init_obj(identity_mtrx(4), SPHERE, m1);
	if (!obj1)
		return (1); //and free data, materials, etc...
	//obj2
	double	*scaling_vector = allocate_tuple(0.5,0.5,0.5,0);
	double	**scaling_matrix = scaling(scaling_vector);//0 for vector?

	//print_grid(scaling_matrix);//too see that both print same thing since identity matrix is just multiplying by 1.
	double	**transform_obj2 = matrix_multiply(identity_mtrx(4), scaling_matrix);
	//print_grid(transform_obj2);

	t_object	*obj2 = init_obj(transform_obj2, SPHERE, m1);//m1 here for testing?
	if (!obj2)
		return (1); //and free data, materials, etc...
	free(scaling_vector);
	free_grid(scaling_matrix);

	//create object list
	lstadd(&obj1, obj2);
 */

/* 	//initiliaze objects for "putting it all together"
	//floor
	double	*scaling_vector = allocate_tuple(10,0.01,10,0);
	double	**scaling_matrix = scaling(scaling_vector);//
	double	**transform_floor = matrix_multiply(identity_mtrx(4), scaling_matrix);
	t_material *materialfoor = init_material(allocate_tuple(1,0.9,0.9,0), 0.0, 0.7, 0, 200.0);
	t_object	*floor = init_obj(transform_floor, SPHERE, materialfoor);
	free(scaling_vector);
	free_grid(scaling_matrix);
	//leftwall
	double	*translation_vector = allocate_tuple(0,0,5,0);
	double	**translation_matrix = translation(translation_vector);
	double	**rotation_y_matrix = rotation_y(-(PI/4));
	double	**rotation_x_matrix = rotation_x((PI/2));
	scaling_vector = allocate_tuple(10,0.01,10,0);
	scaling_matrix = scaling(scaling_vector);
	double **tmp1 = matrix_multiply(rotation_x_matrix, scaling_matrix);
	double **tmp2 = matrix_multiply(rotation_y_matrix, tmp1);
	double **transform_left_wall = matrix_multiply(translation_matrix, tmp2);
	t_object	*left_wall = init_obj(transform_left_wall, SPHERE, materialfoor);
	free(tmp1);
	free(tmp2);
	free(scaling_vector);
	free_grid(scaling_matrix);
	free(translation_vector);
	free_grid(translation_matrix);
	free_grid(rotation_y_matrix);
	free_grid(rotation_x_matrix);
	//rightwall
	translation_vector = allocate_tuple(0,0,5,0);
	translation_matrix = translation(translation_vector);
	rotation_y_matrix = rotation_y(PI/4);
	rotation_x_matrix = rotation_x((PI/2));
	scaling_vector = allocate_tuple(10,0.01,10,0);
	scaling_matrix = scaling(scaling_vector);
	tmp1 = matrix_multiply(rotation_x_matrix, scaling_matrix);
	tmp2 = matrix_multiply(rotation_y_matrix, tmp1);
	double **transform_right_wall = matrix_multiply(translation_matrix, tmp2);
	t_object	*right_wall = init_obj(transform_right_wall, SPHERE, materialfoor);
	free(tmp1);
	free(tmp2);
	free(scaling_vector);
	free_grid(scaling_matrix);
	free(translation_vector);
	free_grid(translation_matrix);
	free_grid(rotation_y_matrix);
	free_grid(rotation_x_matrix);
	//middlesphere
	translation_vector = allocate_tuple(-0.5,1,0.5,0);
	translation_matrix = translation(translation_vector);
	double	**transform_middle = matrix_multiply(identity_mtrx(4), translation_matrix);
	t_material *materialmiddle = init_material(allocate_tuple(0.1,1,0.5,0), 0.0, 0.7, 0.3, 200.0);
	t_object	*middle = init_obj(transform_middle, SPHERE, materialmiddle);
	free(translation_vector);
	free_grid(translation_matrix);
	//rightsphere
	translation_vector = allocate_tuple(1.5,0.5,-0.5,0);
	translation_matrix = translation(translation_vector);
	scaling_vector = allocate_tuple(0.5,0.5,0.5,0);
	scaling_matrix = scaling(scaling_vector);
	double	**transform_right = matrix_multiply(translation_matrix, scaling_matrix);
	t_material *materialright = init_material(allocate_tuple(0.5,1,0.1,0), 0.0, 0.7, 0.3, 200.0);
	t_object	*right = init_obj(transform_right, SPHERE, materialright);
	free(scaling_vector);
	free_grid(scaling_matrix);
	free(translation_vector);
	free_grid(translation_matrix);
	//leftsphere
	translation_vector = allocate_tuple(-1.5,0.33,-0.75,0);
	translation_matrix = translation(translation_vector);
	scaling_vector = allocate_tuple(0.33,0.33,0.33,0);
	scaling_matrix = scaling(scaling_vector);
	double	**transform_left = matrix_multiply(translation_matrix, scaling_matrix);
	t_material *materialleft = init_material(allocate_tuple(1,0.8,0.1,0), 0.0, 0.7, 0.3, 200.0);
	t_object	*left = init_obj(transform_left, SPHERE, materialleft);
	free(scaling_vector);
	free_grid(scaling_matrix);
	free(translation_vector);
	free_grid(translation_matrix);
	//create object list
	lstadd(&floor, left_wall);
	lstadd(&floor, right_wall);
	lstadd(&floor, middle);
	lstadd(&floor, right);
	lstadd(&floor, left);
	//initialize light
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
}//*/

int main(int argc, char **argv) //main Ch.8
{
    t_data 		data;

	(void)argc;
	(void)argv;
    if (ft_minilibx_setup(&data))
		return (perror("minilibx_setup"), 1);

	 //initiliaze objects for "putting it all together"
	//floor
	double	*scaling_vector = allocate_tuple(10,0.01,10,0);
	double	**scaling_matrix = scaling(scaling_vector);
	double	**transform_floor = matrix_multiply(identity_mtrx(4), scaling_matrix);
	t_material *materialfoor = init_material(allocate_tuple(1,0.9,0.9,0), 0.1, 0, 200.0);
	t_object	*floor = init_obj(transform_floor, SPHERE, materialfoor);
	free(scaling_vector);
	free_grid(scaling_matrix);

	//leftwall
	double	*translation_vector = allocate_tuple(0,0,5,0);
	double	**translation_matrix = translation(translation_vector);
	double	**rotation_y_matrix = rotation_y(-(PI/4));
	double	**rotation_x_matrix = rotation_x((PI/2));
	scaling_vector = allocate_tuple(10,0.01,10,0);
	scaling_matrix = scaling(scaling_vector);
	double **tmp1 = matrix_multiply(rotation_x_matrix, scaling_matrix);
	double **tmp2 = matrix_multiply(rotation_y_matrix, tmp1);
	double **transform_left_wall = matrix_multiply(translation_matrix, tmp2);
	t_object	*left_wall = init_obj(transform_left_wall, SPHERE, materialfoor);
	free(tmp1);
	free(tmp2);
	free(scaling_vector);
	free_grid(scaling_matrix);
	free(translation_vector);
	free_grid(translation_matrix);
	free_grid(rotation_y_matrix);
	free_grid(rotation_x_matrix);

	//rightwall
	translation_vector = allocate_tuple(0,0,5,0);
	translation_matrix = translation(translation_vector);
	rotation_y_matrix = rotation_y(PI/4);
	rotation_x_matrix = rotation_x((PI/2));
	scaling_vector = allocate_tuple(10,0.01,10,0);
	scaling_matrix = scaling(scaling_vector);
	tmp1 = matrix_multiply(rotation_x_matrix, scaling_matrix);
	tmp2 = matrix_multiply(rotation_y_matrix, tmp1);
	double **transform_right_wall = matrix_multiply(translation_matrix, tmp2);
	t_object	*right_wall = init_obj(transform_right_wall, SPHERE, materialfoor);
	free(tmp1);
	free(tmp2);
	free(scaling_vector);
	free_grid(scaling_matrix);
	free(translation_vector);
	free_grid(translation_matrix);
	free_grid(rotation_y_matrix);
	free_grid(rotation_x_matrix);

	//middlesphere
	translation_vector = allocate_tuple(-0.5,1,0.5,0);
	translation_matrix = translation(translation_vector);
	double	**transform_middle = matrix_multiply(identity_mtrx(4), translation_matrix);
	t_material *materialmiddle = init_material(allocate_tuple(0.1,1,0.5,0), 0.1, 0.3, 200.0);
	t_object	*middle = init_obj(transform_middle, SPHERE, materialmiddle);
	free(translation_vector);
	free_grid(translation_matrix);

	//rightsphere
	translation_vector = allocate_tuple(1.5,0.5,-0.5,0);
	translation_matrix = translation(translation_vector);
	scaling_vector = allocate_tuple(0.5,0.5,0.5,0);
	scaling_matrix = scaling(scaling_vector);
	double	**transform_right = matrix_multiply(translation_matrix, scaling_matrix);
	t_material *materialright = init_material(allocate_tuple(0.5,1,0.1,0), 0.1, 0.3, 200.0);
	t_object	*right = init_obj(transform_right, SPHERE, materialright);
	free(scaling_vector);
	free_grid(scaling_matrix);
	free(translation_vector);
	free_grid(translation_matrix);

	//leftsphere
	translation_vector = allocate_tuple(-1.5,0.33,-0.75,0);
	translation_matrix = translation(translation_vector);
	scaling_vector = allocate_tuple(0.33,0.33,0.33,0);
	scaling_matrix = scaling(scaling_vector);
	double	**transform_left = matrix_multiply(translation_matrix, scaling_matrix);
	t_material *materialleft = init_material(allocate_tuple(1,0.8,0.1,0), 0.1, 0.3, 200.0);
	t_object	*left = init_obj(transform_left, SPHERE, materialleft);
	free(scaling_vector);
	free_grid(scaling_matrix);
	free(translation_vector);
	free_grid(translation_matrix);

	//create object list
	lstadd(&floor, left_wall);
	lstadd(&floor, right_wall);
	lstadd(&floor, middle);
	lstadd(&floor, right);
	lstadd(&floor, left);

	//initialize light
	t_light	*light;
	light = malloc(sizeof(t_light));
	if (!light)
		return (1);//and free data, etc?
	light->intensity = allocate_tuple(1,1,1,0);//this is just a color multiplier (so not a dot nor a vector)
	light->position = allocate_tuple(-10,10,-10,1);
	t_world	*w = malloc(sizeof(t_world));
	if (!w)
		return (1);//and free data, materials, objects, etc...
	w->light = light;
	w->object = floor;

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
	render_loop(&data, w, c);
    printf("Render finished\n");

    mlx_loop(data.mlx_ptr);

	free(light->intensity);
	free(light->position);

    return (0);
}

/* int main(int argc, char **argv) //main Ch.8
{
    t_data 		data;
	t_world		world;

	(void)argc;
	(void)argv;
    if (ft_minilibx_setup(&data))
		return (perror("minilibx_setup"), 1);

	//parse function
	world = parse_input(argv[1]);

    printf("Starting render\n");
	render_loop(&data, world);
    printf("Render finished\n");

    mlx_loop(data.mlx_ptr);

    return (0);
} */

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

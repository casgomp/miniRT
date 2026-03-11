/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:20:33 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/11 20:08:36 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* 
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
 */

t_material	*init_material(double *color, double ambient, double specular, double shininess)//temporary util to initialize material (eventually done in parsing)
{
	t_material	*m;

	m = malloc(sizeof(t_material));
	if (!m)
		return (NULL);
	m->color = color;//what color?make sure w=0 always for colors.
	m->ambient = ambient;
	m->diffuse = 0.7;
	m->specular = specular;
	m->shininess = shininess;//necessary(yes)?where do we get this value from?;
	return (m);
}

 int	main(int argc, char **argv) //parsing main habibi_merge
{
	t_world		*scene;
	t_data 		data;

	if (argc != 2)
		return (write(2, "Error\nenter one argument only\n", 30), 1);
	if (!file_format_error(argv[1]))
		return (1);

	if (ft_minilibx_setup(&data))
		return (perror("minilibx_setup"), 1);
	
	scene = ft_calloc(1, sizeof(t_world));
	if (!scene)
		return (1);
	scene = parse_input(argv[1], scene);
	print_world(scene);
	

	//init camera view tranform etc;

	//camera
	pixel_size(scene->camera);
	/* double	*from = allocate_tuple(0,1.5,-5,1);
	double	*to = allocate_tuple(0,1,0,1);
	double	*up = allocate_tuple(0,1,0,1); */

	printf("main, scene->camera->transform = \n");
    print_grid(scene->camera->transform);

	//c->transform = view_transform(from, to, up);
	//print_grid(c->transform);

	//init light;
	//init ambient;
	//render_loop(&data, w, c);
	render_loop(&data, scene);
	
	free_world(scene);
	free(scene);
	return (0);
} //*/

/*
int main(int argc, char **argv) //main Ch.8
{
    t_data 		data;

	(void)argc;
	(void)argv;
    if (ft_minilibx_setup(&data))
		return (perror("minilibx_setup"), 1);

	double	**ide_mtrx = identity_mtrx(4);
	
	 //initiliaze objects for "putting it all together"
	//floor
	double	*scaling_vector = allocate_tuple(10,0.01,10,0);
	double	**scaling_matrix = scaling(scaling_vector);
	double	**transform_floor = matrix_multiply(ide_mtrx, scaling_matrix);
	double	color_floor[3] = {1,0.9,0.9};
	t_material *materialfoor = init_material(color_floor, 0.1, 0, 200.0);
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
	double	**transform_middle = matrix_multiply(ide_mtrx, translation_matrix);
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

	double	*from = allocate_tuple(0,1.5,-5,1);
	double	*to = allocate_tuple(0,1,0,1);
	double	*up = allocate_tuple(0,1,0,1);
	c->transform = view_transform(from, to, up);
	//print_grid(c->transform);
	
	render_loop(&data, w, c);

    mlx_loop(data.mlx_ptr);


	//free objects
	free_object_list(floor);
	free_object_list(left_wall);
	free_object_list(right_wall);


	//free light
	free_light_list(light);

	//free utils
	free(ide_mtrx);

    return (0);
} 
//*/
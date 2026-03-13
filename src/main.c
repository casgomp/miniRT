/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:20:33 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/13 17:47:51 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_material	*init_material(double *color, double ambient, double specular, double shininess)//temporary util to initialize material (eventually done in parsing)
{
	t_material	*m;

	m = malloc(sizeof(t_material));
	if (!m)
		return (NULL);

	m->color = color;
	m->ambient = ambient;
	m->diffuse = 0.7;
	m->specular = specular;
	m->shininess = shininess;
	return (m);
}

 int	main(int argc, char **argv)
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
	if (!scene)
		return (1);

	printf("main, scene->camera->transform = \n");
	print_grid(scene->camera->transform);
	render_loop(&data, scene);
	mlx_loop(data.mlx_ptr);
	free_world(scene);
	free(scene);
	return (0);
}

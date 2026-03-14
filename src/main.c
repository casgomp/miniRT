/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:20:33 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/14 16:09:48 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_world		*scene;
	t_data		data;

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
	data.scene = scene;
	render_loop(&data, scene);
	mlx_loop(data.mlx_ptr);
	return (0);
}
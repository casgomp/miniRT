/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:20:33 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/06 19:58:26 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_printf("Program expects single argument: <file>.rt\n"), 1);
	char *test_tmp = argv[1];
	ft_printf("argv[1] = %s\n", test_tmp);
	//parsing of file.rt, opening, reading, etc file.
	//data_init function to store info for geometry, camera, lighting, etc?
	if (!ft_minilibx_setup(&data))
		return (1);//use ft_dprintf to print error message to fd=stderr.
	return (0);
}

int	ft_minilibx_setup(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, "miniRT");
	if (!data->win_ptr)
		return (free(data->win_ptr), 0);//free win_ptr or mlx_ptr?
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	//generate_palette(data)?
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->win_ptr, 17, 0, &handle_destroy_notify, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:20:33 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/13 21:19:32 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_data			data;
	float			**grid_1;
	float			**grid_2;
	t_matrix		matrix;
	t_tuple			tuple;
	int				size;

	(void)argc;
	(void)argv;
	size = 3;
	grid_1 = allocate_grid(size);
	grid_2 = allocate_grid(size);
	grid_1[0][0] = 51;
	grid_1[0][1] = 38;
	grid_1[0][2] = 2;
	grid_1[1][0] = 6;
	grid_1[1][1] = 8;
	grid_1[1][2] = 10;
	grid_1[2][0] = 22;
	grid_1[2][1] = 31;
	grid_1[2][2] = 11;
	grid_1[3] = NULL;

	grid_2[0][0] = 83;
	grid_2[0][1] = 9;
	grid_2[0][2] = 0;
	grid_2[1][0] = 14;
	grid_2[1][1] = 22;
	grid_2[1][2] = 65;
	grid_2[2][0] = 0;
	grid_2[2][1] = 2;
	grid_2[2][2] = 9;
	grid_1[3] = NULL;

	matrix.grid = matrix_multiply(grid_1, grid_2);
	tuple = construct_tuple(5.5, 6.25, 3.33, 0);
	matrix = construct_matrix(matrix.grid);
	print_grid(matrix.grid);
	printf("\n %f", matrix.determinant);
	print_grid(matrix.transpose);
	printf("\n");
	print_grid(matrix.inverse);
	printf("\n");
	free_matrix(&matrix);
	free_grid(grid_1);
	free_grid(grid_2);
	free_tuple(&tuple);
	if (!ft_minilibx_setup(&data))
		return (1);
	return (0);
}

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
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->win_ptr, 17, 0, handle_destroy_notify, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

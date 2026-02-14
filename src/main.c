/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:20:33 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/14 16:32:53 by aabdella         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data			data;
	t_matrix		matrix;
	t_tuple			tuple;
	int				size;
	double			**grid_1;
	double			**grid_2;

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
	tuple = construct_tuple(5.5, 6.25, 3.33, 0);
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

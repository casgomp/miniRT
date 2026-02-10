/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:20:33 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/10 16:51:23 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_matrix		*matrix;
	t_matrix		*matrix_2;
	t_matrix		*matrix_3;
	int				size;

	(void)argc;
	(void)argv;
	size = 3;
	matrix = ft_calloc(1, sizeof(t_matrix));
	matrix_2 = ft_calloc(1, sizeof(t_matrix));
	matrix->grid = allocate_matrix(size);
	matrix_2->grid = allocate_matrix(size);
	matrix->size = size;
	matrix_2->size = size;
	matrix->grid[0][0] = 5;
	matrix->grid[0][1] = 3;
	matrix->grid[1][0] = 2;
	matrix->grid[1][1] = 1;
	matrix_2->grid[0][0] = 8;
	matrix_2->grid[0][1] = 9;
	matrix_2->grid[1][0] = 0;
	matrix_2->grid[1][1] = 4;
	matrix_3 = matrix_multiply(matrix, matrix_2);
	print_matrix(matrix_3);
	free_matrix(matrix);
	free_matrix(matrix_2);
	free_matrix(matrix_3);
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

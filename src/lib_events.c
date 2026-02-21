/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:11:34 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/21 15:26:33 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	handle_destroy_notify(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	terminate(data, 0, NULL);
	return (0);
}

int	handle_keypress(int keysym, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keysym == XK_Escape)
		terminate(data, 0, NULL);
	return (0);
}

void	terminate(t_data *data, int exit_code, char *error_msg)
{
	if (data->img.mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (error_msg)
		perror(error_msg);
	exit(exit_code);
}

void	free_grid(double **grid)
{
	int	i;
	int	size;

	i = 0;
	size = grid_size(grid);
	while (i < size)
	{
		free(grid[i]);
		i ++;
	}
	free(grid);
	grid = NULL;
}

void	free_matrix(t_matrix *matrix)
{
	free_grid(matrix->grid);
	free_grid(matrix->transpose);
	free_grid(matrix->inverse);
	matrix -> grid = NULL;
	matrix -> transpose = NULL;
	matrix -> inverse = NULL;
}

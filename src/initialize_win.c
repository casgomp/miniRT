/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:11:34 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/09 16:45:35 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	window_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		write(2, MLX_ERR, ft_strlen(MLX_ERR));
		close_window(data, 1);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1980, 1080, "miniRT_scene");
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_hook, data);
	mlx_loop(data->mlx_ptr);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data, 0);
	return (0);
}

int	close_window(t_data *data, int exit_code)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data -> mlx_ptr);
	free(data -> mlx_ptr);
	exit(exit_code);
	return (exit_code);
}

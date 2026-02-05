/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:11:34 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/04 20:36:39 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	window_init(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
	{
		write(2, MLX_ERR, ft_strlen(MLX_ERR));
		close_window(scene, 1);
	}
	scene->win = mlx_new_window(scene->mlx, 1980, 1080, "miniRT_scene");
	mlx_hook(scene->win, 17, 0, close_window, scene);
	mlx_hook(scene->win, 2, 1L << 0, key_hook, scene);
	mlx_loop(scene->mlx);
}

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == ESC)
		close_window(scene, 0);
	return (0);
}

int	close_window(t_scene *scene, int exit_code)
{
	mlx_destroy_window(scene->mlx, scene->win);
	mlx_destroy_display(scene -> mlx);
	free(scene -> mlx);
	exit(exit_code);
	return (exit_code);
}

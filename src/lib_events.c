/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:11:34 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/10 16:58:11 by aabdella         ###   ########.fr       */
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

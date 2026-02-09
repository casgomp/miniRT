/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:33:44 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/09 16:50:46 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define RD_ERR "read file failure\n"
# define MALL_ERR "memory allocation failure\n"
# define OPEN_ERR "open file failed\n"
# define MLX_ERR "mlx_intialization failure\n"
# define ESC 0xff1b
# define GREEN_PIXEL 0xFF00
# define RED_PIXEL 0xFF0000

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}t_img;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

typedef struct l_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}t_data;

void	window_init(t_data *scene);
int		close_window(t_data *scene, int exit_code);
int		key_hook(int keycode, t_data *scene);
//int		render_rect(t_data *data, t_rect rect);
int		render(t_data *data);
#endif

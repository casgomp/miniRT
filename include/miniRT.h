/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:33:44 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/10 16:57:00 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

# define RD_ERR "read file failure\n"
# define MALL_ERR "memory allocation failure\n"
# define OPEN_ERR "open file failed\n"
# define MLX_ERR "mlx_intialization failure\n"
# define ESC 0xff1b
# define WIN_W 800
# define WIN_H 800
# define GREEN_PIXEL 0xFF00
# define RED_PIXEL 0xFF0000

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			exit_code;
	char		*error_msg;
	t_img		img;

}t_data;

typedef struct s_matrix
{
	int		**grid;
	int		size;
	int		**transpose;
	int		determinant;
}	t_matrix;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

//main
int			main(int argc, char **argv);
int			ft_minilibx_setup(t_data *data);

//lib_events
int			handle_destroy_notify(void *param);
int			handle_keypress(int keysym, void *param);

//rendering
int			render(t_data *data);
int			render_rect(t_data *data, t_rect rect);
void		img_pix_put(t_img *img, int x, int y, int color);
void		terminate(t_data *data, int exit_code, char *error_msg);

//matrix
void		print_matrix(t_matrix *matrix);
int			**allocate_matrix(int size);
void		free_matrix(t_matrix *matrix);
t_matrix	*matrix_multiply(t_matrix *matrix_1, t_matrix *matrix_2);

#endif

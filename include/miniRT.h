/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:33:44 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/14 17:46:42 by aabdella         ###   ########.fr       */
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
# define PI 3.14159265358979323846
# define ESC 0xff1b
# define WIN_W 800
# define WIN_H 800
# define GREEN_PIXEL 0xFF00
# define RED_PIXEL 0xFF0000

typedef enum e_TUPLE_TYP
{
	VECTOR,
	POINT,
}	t_TUPLE_TYP;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			exit_code;
	char		*error_msg;
	t_img		img;

}	t_data;

typedef struct s_matrix
{
	double	**grid;
	int		size;
	double	**transpose;
	double	**inverse;
	double	determinant;
}	t_matrix;

typedef struct s_tuple
{
	double			*tuple;
	t_TUPLE_TYP		tuple_type;
	double			*unit_vector;
	double			magnitude;
}	t_tuple;

typedef struct s_rect
{
	double	x;
	double	y;
	double	width;
	double	height;
	int		color;
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

//matrix utils
void		print_grid(double **grid);
double		**allocate_grid(int size);
void		free_grid(double **grid);
void		free_matrix(t_matrix *matrix);
double		**matrix_multiply(double **grid_1, double **grid_2);
int			grid_size(double **grid);
double		**duplicate_grid(double **grid);

//construct matrix
double		**inverse(double **grid, int size);
double		**tranpose_grid(double **tmtrx);
t_matrix	construct_matrix(double **grid);
double		**get_submatrix(double **mtrx, int size, int rowskip, int colskip);
double		cofactor(double **mtrx, int size, int row, int col);
double		**identity_mtrx(int size);

//tuples
t_tuple		construct_tuple(double x, double y, double z, double w);
void		normalize_vector(t_tuple *vector);
void		free_tuple(t_tuple *tuple);
double		determinant(double **grid, int size);


#endif

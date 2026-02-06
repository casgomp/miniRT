/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:33:44 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/06 19:58:28 by pecastro         ###   ########.fr       */
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

//# define RD_ERR "read file failure\n" //this should be perror
//# define MALL_ERR "memory allocation failure\n" //this should be perror
//# define OPEN_ERR "open file failed\n" //this should be perror
//# define MLX_ERR "mlx_intialization failure\n" //This with ft_dprintf (add to libft)
# define ESC 0xff1b
# define WIN_W 800
# define WIN_H 800

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
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	//data for for geometry, camera, lighting, etc?
}t_data;

//rect is just for testing:
typedef struct s_rect
{
    int	x;
    int	y;
    int width;
    int height;
    int color;
}	t_rect;


//main
int			main(int argc, char **argv);
int			ft_minilibx_setup(t_data *data);
//void		ft_data_initialize(t_data *data);

//lib_events
int handle_destroy_notify(t_data *data);
int handle_keypress(int keysym, t_data *data);

//rendering
int render(t_data *data);
//rect function is just for testing:
int render_rect(t_data *data, t_rect rect);
void  img_pix_put(t_img *img, int x, int y, int color);

//void		window_init(t_scene *scene);
//int		close_window(t_scene *scene, int exit_code);
//int		key_hook(int keycode, t_scene *scene);

#endif

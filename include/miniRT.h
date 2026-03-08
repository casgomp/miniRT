/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:33:44 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/08 19:32:25 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
#include "mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <sys/time.h>

# define RD_ERR "read file failure\n"
# define MALL_ERR "memory allocation failure\n"
# define OPEN_ERR "open file failed\n"
# define MLX_ERR "mlx_intialization failure\n"
# define PI 3.14159265358979323846
# define ESC 0xff1b
# define WIN_W 800 //800 is good size
# define WIN_H 800
//# define GREEN_PIXEL 0xFF00
//# define RED_PIXEL 0xFF0000
# define BLACK_PIXEL 0X000

typedef enum e_TUPLE_TYP
{
	VECTOR,
	POINT,
}	t_TUPLE_TYP;

typedef enum e_OBJECT_TYP
{
	SPHERE,
	CYLINDER,
	PLANE,
	CAMERA,
	LIGHT,
	AMBIENT_LIGHT,
}	t_OBJECT_TYP;

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
	double			*unit_vector;//can delete and simply override the double *tuple with unit vecotr. In case we need original back multiply unit*magnitude
	double			magnitude;
}	t_tuple;

typedef struct s_plane
{
	double	x;
	double	y;
	double	width;
	double	height;
	int		color;
}	t_plane;

typedef struct s_rect
{
	double	x;
	double	y;
	double	width;
	double	height;
	int		color;
}	t_rect;

typedef struct s_cylinder
{
	double	x;
	double	y;
	double	width;
	double	height;
	int		color;
}	t_cylinder;

typedef struct s_sphere //probably won't need individual shape structs.
{
	double	radius;
	double	*center;
	double	**transform;
}	t_sphere;

typedef struct t_material
{
	double	*color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef struct s_object
{
	int					object_id;
	t_OBJECT_TYP		object_type;
	double				**transform;
	double				**inverse;
	double				angle;
	double				*scale;
	int					*rgb;
	double				brightness;
	t_material			*material;
	struct s_object		*next;
}	t_object;

//temp intersection struct for the camera file.
/*typedef struct s_intersection
{
	double		t;
	t_sphere	*sphere;
} t_intersection;*/

//temp intersection struct for the camera file v2.
typedef struct s_intersection
{
	double		t;
	t_object	*obj;
} t_intersection;

typedef struct s_intersection_lst
{
	double						*t;
	double						**points_lst;
	double						hit;
	double						*hit_points;
	double						object_id;
	struct s_intersection_lst	*next;
}	t_instersection_lst;

typedef struct s_ray
{
	double					*ray_origin;
	double					*ray_direction;
	t_instersection_lst		*intersection_lst;
}	t_ray;


typedef struct s_light
{
	double	*position;
	double	*intensity;
}	t_light;

typedef struct s_world
{
	t_object	*object;
	t_light		*light;
}	t_world;

typedef struct s_camera
{
	double	hsize;
	double	vsize;
	double	field_of_view;
	double	**transform;
	double	pixel_size;
	double	half_width;
	double	half_height;
}	t_camera;

typedef struct s_comps
{
	double		t;
	t_object	*obj;
	double		*point;
	double		*eyev;
	double		*normalv;
	bool		inside;
}	t_comps;


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
int			grid_size(double **grid);//might cause SIGSEV?
double		**duplicate_grid(double **grid);
double		**rotation_x(double r);
double		**rotation_y(double r);
double		**rotation_z(double r);
double		**scaling(double *coord);
double		**translation(double *coord);

//construct matrix
double		**inverse(double **grid, int size);
double		**transpose_grid(double **tmtrx);
t_matrix	construct_matrix(double **grid);
double		**get_submatrix(double **mtrx, int size, int rowskip, int colskip);
double		cofactor(double **mtrx, int size, int row, int col);
double		**identity_mtrx(int size);

//tuples
t_tuple		construct_tuple(double x, double y, double z, double w);
//void		normalize_vector(t_tuple *vector);
void		normalize_vector(double *vector);
void		free_tuple(t_tuple *tuple);
double		determinant(double **grid, int size);
double		*allocate_tuple(double x, double y, double z, double w);
double		degrees_to_radians(double degrees);
double		radians_to_degrees(double radians);
double		**tuple_to_matrix(double *tuple, int i);
double		*matrix_to_tuple(double **grid);
double		*rotate_tuple_x(double *tuple, double angle);
double		*rotate_tuple_y(double *tuple, double angle);
double		*rotate_tuple_z(double *tuple, double angle);
double		*scale_tuple(double *tuple);
double		*translate_tuple(double *tuple);
double		*cross_product(double *vector_1, double *vector_2);
double		*add_tuple(double *tuple_1, double *tuple_2);
double		*subtract_tuple(double *tuple_1, double *tuple_2);
double		dot_product_tuple(double *tuple_1, double *tuple_2);

/*//test_camera
t_intersection	*intersection(t_ray r, t_sphere *s);
t_intersection	*intersect_list_append(t_intersection *xs,
							t_intersection *xslst, int *count, int *capacity);
int				get_pixel_color(t_ray r, t_sphere *s);
void			render_loop(t_data *data, t_sphere *s);
//*/

//test_camera2
t_intersection	*intersection2(t_ray r, t_object *s);
t_intersection	*intersect_list_append2(t_intersection *xs,
							t_intersection *xslst, int *count, int *capacity);
//int				get_pixel_color2(t_ray r, t_object *objp, t_light *light);
double			*color_at(t_world *world, t_ray ray);
//void			render_loop2(t_data *data, t_object *s, t_light *light);
//void			render_loop2(t_data *data, t_world *w);
void			render_loop2(t_data *data, t_world *w, t_camera *c);

//utils
t_ray   transform_ray(t_ray r, double **m);//or simple t_matrix
double  *multiply_matrix_tuple(double **m, double *t);
double  *multiply_tuple_tuple(double *t1, double *t2);
double  *normal_at(t_object *object, double *world_point);
double  *ray_position(t_ray r, double t);
//void    *point_light(double  *intensity, double *position);
int 	color_to_int(double *color_percent);
void remap_rgb(int r, int g, int b, double *color);
void	lstadd(t_object **lst, t_object *new);
t_object	*lstlast(t_object *lst);
t_comps	*prepare_computations(t_intersection *intersection, t_ray ray);
double	*shade_hit(t_world *world, t_comps *comps);

//main ch.7 utils
t_object	*init_obj(double **transform, t_OBJECT_TYP object_type, t_material *m);
t_material	*init_material(double *color, double ambient, double diffuse, double specular, double shininess);

//implement_camera
double  	**view_transform(double *from, double *to, double *up);
t_camera    *camera(double hsize, double vsize, double field_of_view);
void  		pixel_size(t_camera *c);
t_ray		*ray_for_pixel(t_camera *c, double px, double py);

//lightshade
double  *reflect(double *in, double *w_normal);
double  *lighting(t_material *material, t_light *light, double *hit_point, double *eyev, double *normalv);//can only take 4 params

//construct intersections
double		*ray_sphere_intersection(double *ray_origin,
				double *ray_direction, double *sphere_center);
double		**ray_sphere_points(double *ray_origin, double *ray_direction,
				double *t);
double		*get_discriminant(double *ray_origin, double *ray_direction,
				double *sphere_origin);
double		*multiply_scalar(double *tuple, double scalar);

// parsing
int			parse_ambient(char **data, t_object **lst, int i);
int			parse_camera(char **data, t_object **lst, int id);
int			parse_light(char **data, t_object **lst, int id);
int			parse_sphere(char **data, t_object **lst, int id);
int			parse_plane(char **data, t_object **lst, int id);
int			parse_cylinder(char **data, t_object **lst, int id);
t_object	*parse_input(char *input, t_object *lst);

// parsing_utils
int			print_error(int fd, const char *msg);
int			file_format_error(char *filename);
double		*str_to_double(char *str, double i);
int			*str_to_int(char *str, int i);
int			rgb_parse(char *rgb);
int			is_normal_vec(char *vec_str);
double		**align_to_vec(char *identifier_2, double **matrix);
void		print_object_list(t_object *lst);
t_object	*append_object_lst(t_object **lst, t_object *new);
void		free_object_list(t_object *lst);
#endif

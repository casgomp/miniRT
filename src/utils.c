/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:52:57 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/04 21:39:18 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//utils tuple
double  *multiply_matrix_tuple(double **m, double *t)
{
    double  *res;
    int     i;
    static int b = 1;

    res = malloc(sizeof(double) * 4);
    if (!res)
        return (NULL);
    i = -1;
    while (++i < 4)
    {
        res[i] = (m[i][0] * t[0]) +
                 (m[i][1] * t[1]) +
                 (m[i][2] * t[2]) +
                 (m[i][3] * t[3]);
    }
    b ++;
    return (res);
}

double  *multiply_tuple_tuple(double *t1, double *t2)
{
    double  *new;
    int     i;

    new = ft_calloc(4, sizeof(double));
    if (!new)
        return (NULL);
    i = -1;
    while (++i < 4)
        new[i] = t1[i] * t2[i];
    return (new);
}

//utils ray tranformation
t_ray   transform_ray(t_ray r, double **m)//double or a simple t_matrix works too.
{
    t_ray   new_ray;

    new_ray.ray_origin = multiply_matrix_tuple(m, r.ray_origin);
    new_ray.ray_direction = multiply_matrix_tuple(m, r.ray_direction);
    return (new_ray);
}

//utils world normal
double  *ray_position(t_ray r, double t)
{
    double  *scaled_dir;
    double  *pos;

    scaled_dir = multiply_scalar(r.ray_direction, t);
    pos = add_tuple(r.ray_origin, scaled_dir);
    free (scaled_dir);
    return (pos);
}

double  *normal_at(t_object *object, double *world_point)
{
    double  *local_point;
    double  *local_normal;
    double  **transposed_inverse;
    double  *world_normal;
    
    local_point = multiply_matrix_tuple(object->inverse, world_point);
    local_normal = NULL;
    if (object->object_type == 1)//SPHERE
        local_normal = allocate_tuple(local_point[0], local_point[1], local_point[2], 0);
    else if (object->object_type == 2)//CYLINDER
        local_normal = allocate_tuple(local_point[0], 0, local_point[2], 0);
    else if (object->object_type == 3)//PLANE
        local_normal = allocate_tuple(0, 1, 0, 0);
    transposed_inverse = transpose_grid(object->inverse);
    world_normal = multiply_matrix_tuple(transposed_inverse, local_normal);
    world_normal[3] = 0;//must do this little trick (see p.82)
    normalize_vector(world_normal);
    free(local_point);
    free(local_normal);
    free_grid(transposed_inverse);
    return (world_normal);
}

//utils reflect
double  *reflect(double *in, double *w_normal)
{
    double  scalar;
    double  *vector;
    double  *reflectv;

    //in - normal * 2 * dot(in, normal)
    scalar = 2 * dot_product_tuple(in, w_normal);
    vector = multiply_scalar(w_normal, scalar);
    reflectv = subtract_tuple(in, vector);
    return (reflectv);
}

//utils lighting
double  *lighting(t_material *material, t_light *light, double *hit_point, double *eyev, double *normalv)//can only take 4 params
{
    double  *effective_color;
    double  *lightv;
    double  *lightv_neg;
    double  *ambient;
    double  *diffuse;
    double  *specular;
    double  light_dot_normal;
    double  *reflectv;
    double  reflect_dot_eye;
    double  factor;
    double  *result;

    lightv_neg = allocate_tuple(-1,-1,-1,0);
    effective_color = multiply_tuple_tuple(material->color, light->intensity);
    lightv = subtract_tuple(light->position, hit_point);
    normalize_vector(lightv);
    ambient = multiply_scalar(effective_color, material->ambient);
    light_dot_normal = dot_product_tuple(lightv, normalv);
    if (light_dot_normal < 0)
    {
        diffuse = allocate_tuple(0,0,0,0);
        specular = allocate_tuple(0,0,0,0);
    }
    else
    {
        diffuse = multiply_scalar(effective_color, material->diffuse * light_dot_normal);
        lightv_neg = multiply_tuple_tuple(lightv, lightv_neg);
        reflectv = reflect(lightv_neg, normalv);
        reflect_dot_eye = dot_product_tuple(reflectv, eyev);
        if (reflect_dot_eye <= 0)
            specular = allocate_tuple(0,0,0,0);
        else
        {
            factor = pow(reflect_dot_eye, material->shininess);//what to use for shininess;
            specular = multiply_scalar(light->intensity, material->specular * factor);
        }
    }

    free(effective_color);
    free(lightv);
    free(lightv_neg);
    free(ambient);
    //free all double* variables.

    result = add_tuple(ambient,diffuse);
    result = add_tuple(result, specular);
    return (result);
}

int color_to_int(double *color_percent)
{
    int rgb;
    int i;
    int color;

    if (!color_percent)
        return (0);
    //store individual colors in standard 255 value range and correct when overflow.
    //use OR to put all rgb bits into color
    rgb = 0;
    color = 0;
    i = -1;
    while (++i < 3)
    {
        rgb = color_percent[i] * 255.99;
        if (rgb > 255)
            rgb = 255;
        else if (rgb < 0)
            rgb = 0;
        if (i < 2)
            rgb <<= (2 - i) * 8;
        color |= rgb;
    }
    return (color);
}

//create list utils
void	lstadd(t_object **lst, t_object *new)
{
	t_object	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = lstlast(*lst);
	last -> next = new;
}

t_object	*lstlast(t_object *lst)
{
	t_object	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while ((tmp -> next) != NULL)
		tmp = tmp -> next;
	return (tmp);
}
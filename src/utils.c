/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:52:57 by pecastro          #+#    #+#             */
/*   Updated: 2026/02/27 16:22:59 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//utils ray tranformation
t_ray   transform_ray(t_ray r, double **m)//double or a simple t_matrix works too.
{
    t_ray   new_ray;

    new_ray.ray_origin = multiply_matrix_tuple(m, r.ray_origin);
    new_ray.ray_direction = multiply_matrix_tuple(m, r.ray_direction);
    return (new_ray);
}

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:57:26 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/14 11:40:06 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double  **view_transform(double *from, double *to, double *up)//what parameter data types?
{
    double  *from_neg;
    double  *forward;
    double  *forward_neg;
    double  *left;
    double  *true_up;
    double  *negative;
    double  **translate;
    double  **transform;
    double  **idemtrx;
    int     i;
    
    forward = subtract_tuple(to, from);
    //add function to check if magnitude < 0.00001 to prevent division by zero.
    normalize_vector(forward);
    normalize_vector(up);
    left = cross_product(forward, up);
    true_up = cross_product(left, forward);
    negative = allocate_tuple(-1,-1,-1,0);
    forward_neg = multiply_tuple_tuple(forward, negative);//-forward
    idemtrx = identity_mtrx(4);
    i = -1;
    while (++i < 3)
        idemtrx[0][i] = left[i];
    i = -1;
    while (++i < 3)
        idemtrx[1][i] = true_up[i];
    i = -1;
    while (++i < 3)
        idemtrx[2][i] = forward_neg[i];

    from_neg = multiply_tuple_tuple(from, negative);//-from
    translate = translation(from_neg);

    transform = matrix_multiply(idemtrx, translate);

    free(from_neg);
    free(forward);
    free(forward_neg);
    free(left);
    free(true_up);
    free(negative);
    free_grid(idemtrx);
    free_grid(translate);
    
    return (transform);
}

t_camera    *camera(double hsize, double vsize, double field_of_view)
{
    t_camera    *c;

    c = malloc(sizeof(t_camera));
    if (!c)
        return (NULL);
    c->hsize = hsize;
    c->vsize = vsize;
    c->field_of_view = field_of_view;
    c->transform = identity_mtrx(4);
    return (c);
}

void  pixel_size(t_camera *c)
{
    double  half_view;
    double  aspect;

    half_view = tan(c->field_of_view / 2);
    aspect = c->hsize / c->vsize;
    if (aspect >= 1)
    {
        c->half_width = half_view;
        c->half_height = half_view / aspect;
    }
    else
    {
        c->half_width = half_view * aspect;
        c->half_height = half_view;
    }
    c->pixel_size = (c->half_width * 2) / c->hsize;
}

t_ray  *ray_for_pixel(t_camera *c, double px, double py)
{
    double  xoffset;
    double  yoffset;
    double  world_x;
    double  world_y;
    double  **inv_transform;
    double  *point_w;
    double  *point;
    double  *pixel;
    t_ray   *r;

    r = malloc(sizeof(t_ray));
    if (!r)
        return (NULL);
    xoffset = (px + 0.5) * c->pixel_size;
    yoffset = (py + 0.5) * c->pixel_size;
    world_x = c->half_width - xoffset;
    world_y = c->half_height - yoffset;
    inv_transform = inverse(c->transform, 4);
    if (!inv_transform)
        return (NULL);
    point_w = allocate_tuple(world_x, world_y, -1, 1);//w=1
    pixel = multiply_matrix_tuple(inv_transform, point_w);
    point = allocate_tuple(0,0,0,1);//w=1
    r->ray_origin = multiply_matrix_tuple(inv_transform, point);
    r->ray_direction = subtract_tuple(pixel, r->ray_origin);
    normalize_vector(r->ray_direction);

    free_grid(inv_transform);
    free(point_w);
    free(point);
    free(pixel);

    return (r);
}
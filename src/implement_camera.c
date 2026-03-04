/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:57:26 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/04 21:39:14 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double  **view_transform(double *from, double *to, double *up)//what parameter data types?
{
    double  *forward;
    double  *left;
    double  *true_up;
    double  *negative;
    double  **translate;
    double  **transform;
    int     i;
    
    forward = subtract_tuple(to, from);
    normalize_vector(forward);
    normalize_vector(up);
    left = cross_product(forward, up);
    true_up = cross_product(left, forward);
    negative = allocate_tuple(-1,-1,-1,0);
    forward = multiply_tuple_tuple(forward, negative);//-forward
    transform = identity_mtrx(4);
    i = -1;
    while (++i < 3)
        transform[0][i] = left[i];
    i = -1;
    while (++i < 3)
        transform[1][i] = true_up[i];
    i = -1;
    while (++i < 3)
        transform[2][i] = forward[i];

    from = multiply_tuple_tuple(from, negative);//-from
    translate = translation(from);

    transform = matrix_multiply(transform, translate);

    free(forward);
    free(left);
    free(true_up);
    free(negative);
    free_grid(translate);

    return (transform);
}
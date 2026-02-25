/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:52:57 by pecastro          #+#    #+#             */
/*   Updated: 2026/02/25 19:29:04 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray   transform_ray(t_ray r, double **m)//or simple t_matrix
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
    return (res);
}
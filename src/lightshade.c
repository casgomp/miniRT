/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightshade.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:21:06 by pecastro          #+#    #+#             */
/*   Updated: 2026/02/25 19:29:07 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double  *normal_at(t_sphere *s, double *p) //p = eventually same function calculates also other objects
{
    double  *vector;

    vector = subtract_tuple(p, s->center);
    return (vector);
}

double  *lightshade_test(t_sphere *s, double *p) //p = eventually same function calculates also other objects
{
    double  *normal;
    
    normal = normal_at(s, p);
    normalize_vector(normal);
    return (normal);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightshade.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:21:06 by pecastro          #+#    #+#             */
/*   Updated: 2026/02/26 15:16:56 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* //no need for this function, since in object space, the point of intersection is already the normal.
double  *normal_at(t_sphere *s, double *p) //p = eventually same function calculates also other objects
{
    double  *vector;

    vector = subtract_tuple(p, s->center);
    return (vector);
}//*/

/*//no need for this function, since in object space, the point of intersection is already the normal.
double  *lightshade_test(t_sphere *s, double *p) //p = eventually same function calculates also other objects
{
    double  *normal;
    
    normal = normal_at(s, p);
    normalize_vector(normal);
    return (normal);
}//*/
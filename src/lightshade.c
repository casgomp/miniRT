/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightshade.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:21:06 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/08 12:34:32 by pecastro         ###   ########.fr       */
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
        lightv_neg = multiply_tuple_tuple(lightv, lightv_neg);//this is memory leak for sure not freeing prev lightv_neg
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

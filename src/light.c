/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:21:06 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/10 09:11:29 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double  *reflect(double *in, double *w_normal)
{
    double  scalar;
    double  *vector;
    double  *reflectv;

    scalar = 2 * dot_product_tuple(in, w_normal);
    vector = multiply_scalar(w_normal, scalar);
    reflectv = subtract_tuple(in, vector);
    return (reflectv);
}

double  *lighting(t_material *material, t_light *light, double *hit_point, double *eyev, double *normalv, bool in_shadow)//can only take 4 params
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

    effective_color = multiply_tuple_tuple(material->color, light->intensity);
    ambient = multiply_scalar(effective_color, material->ambient);
    if (in_shadow)
    {
        free(effective_color);
        printf("color = (%f,%f,%f\n)", ambient[0],ambient[1],ambient[2]);
        return(ambient);
    }
    lightv_neg = allocate_tuple(-1,-1,-1,0);//better create a general negative tuple to avoid memory leaks later
    lightv = subtract_tuple(light->position, hit_point);
    normalize_vector(lightv);
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

double  *normal_at(t_object *object, double *world_point)
{
    double  *local_point;
    double  *local_normal;
    double  **transposed_inverse;
    double  *world_normal;
    
    local_point = multiply_matrix_tuple(object->inverse, world_point);
    local_normal = NULL;
    if (object->object_type == SPHERE)
        local_normal = allocate_tuple(local_point[0], local_point[1], local_point[2], 0);
    else if (object->object_type == CYLINDER)
        local_normal = allocate_tuple(local_point[0], 0, local_point[2], 0);
    else if (object->object_type == PLANE)
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

double  *ray_position(t_ray r, double t)
{
    double  *scaled_dir;
    double  *pos;

    scaled_dir = multiply_scalar(r.ray_direction, t);
    pos = add_tuple(r.ray_origin, scaled_dir);
    free (scaled_dir);
    return (pos);
}

t_comps	*prepare_computations(t_intersection *intersection, t_ray ray)
{
	t_comps			*comps;
	double			*negative;

	comps = malloc(sizeof(t_comps));
	if (!comps)
		return (NULL);
	
	comps->t = intersection->t;
	comps->obj = intersection->obj;

	negative = allocate_tuple(-1,-1,-1,0);
	comps->point = ray_position(ray, comps->t);//point is the hit point
	comps->eyev = multiply_tuple_tuple(ray.ray_direction, negative);
	comps->normalv = normal_at(comps->obj, comps->point);

	if (dot_product_tuple(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = true;
		comps->normalv = multiply_tuple_tuple(comps->normalv, negative);
	}
	else
		comps->inside = false;

	free(negative);

	return (comps);
}
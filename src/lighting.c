/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:25:57 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/16 15:34:53 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	is_shadowed(t_world *world, double *point)
{
	double			*vector;
	double			distance;
	int				count;
	t_ray			*r;
	t_intersection	*xs;
	t_intersection	*hit;

	r = malloc(sizeof(t_ray));
	if (!r)
		return (NULL);
	vector = subtract_tuple(world->light->position, point);
	distance = get_vector_magnitude(vector);
	r->ray_origin = point;
	r->ray_direction = vector;
	vector = NULL;
	normalize_vector(r->ray_direction);
	//create new function for this next part xs and hit are now in other function:
	xs = intersect_world(world, *r, &count);
	hit = check_if_hit(xs, &count);
	free(r->ray_direction);
	free(r);
	if (hit && hit->t < distance)
		return (free(xs), true);
	else
		return (free(xs), false);
}

double	*shade_hit(t_world *world, t_comps *comps)
{
	bool	in_shadow;
	double	*tmp;
	double	*color;
	double	*old_color;
	t_light	*current_light;

	in_shadow = is_shadowed(world, comps->point);
	color = NULL;
	old_color = NULL;
	if (world->ambient)
	{
		color = multiply_tuple_tuple(comps->obj->material->color, 
				world->ambient->rgb);
		old_color = color;
		color = multiply_scalar(color, 
				comps->obj->material->ambient * world->ambient->intensity[0]);
		free(old_color);
		old_color = NULL;
	}
	else
		color = allocate_tuple(0, 0, 0, 0);
	current_light = world->light;
	while (current_light)
	{
		tmp = lighting(comps->obj->material, current_light, 
				comps->point, comps->eyev, comps->normalv, in_shadow);
		old_color = color;
		color = add_tuple(color, tmp);
		free(old_color);
		free(tmp);
		current_light = current_light->next;
	}
	return (color);
}

double	*reflect(double *in, double *w_normal)
{
	double	scalar;
	double	*vector;
	double	*reflectv;

	scalar = 2 * dot_product_tuple(in, w_normal);
	vector = multiply_scalar(w_normal, scalar);
	reflectv = subtract_tuple(in, vector);
	free(vector);
	return (reflectv);
}

double  *lighting(t_material *material, t_light *light, double *hit_point, double *eyev, double *normalv, bool in_shadow)//can only take 4 params
{
    double  *effective_color;
    double  *lightv;
    double  *negative;
    double  *lightv_neg;
    double  *ambient;
    double  *diffuse;
    double  *specular;
    double  light_dot_normal;
    double  *reflectv;
    double  reflect_dot_eye;
    double  factor;
    double  *tmp;
    double  *result;

    reflectv = NULL;
    lightv_neg = NULL;
    effective_color = multiply_tuple_tuple(material->color, light->intensity);
    ambient = multiply_scalar(effective_color, material->ambient);
    if (in_shadow)
        return(free(effective_color), ambient);//just ambient or ambient light too?
    negative = allocate_tuple(-1,-1,-1,0);
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
        lightv_neg = multiply_tuple_tuple(lightv, negative);
        reflectv = reflect(lightv_neg, normalv);
        reflect_dot_eye = dot_product_tuple(reflectv, eyev);
        if (reflect_dot_eye <= 0)
            specular = allocate_tuple(0,0,0,0);
        else
        {
            factor = pow(reflect_dot_eye, material->shininess);
            specular = multiply_scalar(light->intensity, material->specular * factor);
        }
    }
    tmp = add_tuple(ambient,diffuse);
    result = add_tuple(tmp, specular);
    free(effective_color);
    free(ambient);
    free(lightv);
    free(negative);
    free(lightv_neg);
    free(reflectv);
    free(diffuse);
    free(tmp);
    free(specular);
    return (result);
}
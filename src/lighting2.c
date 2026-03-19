/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:55:38 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/19 14:50:55 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*get_effective_color(t_light *light, t_comps *comps)
{
	double	*light_color;
	double	*effective_color;

	light_color = multiply_scalar(light->rgb, light->intensity[0]);
	effective_color = multiply_tuple_tuple(comps->obj->material->color, 
			light_color);
	free(light_color);
	return (effective_color);
}

double	*get_ambient(double *effective_color, t_comps *comps)
{
	double	*ambient;

	ambient = multiply_scalar(effective_color, comps->obj->material->ambient);
	free (effective_color);
	return (ambient);
}

double	*get_result_color(double *diffuse, double *specular, 
		double *effective_color, t_comps *comps)
{
	double	*tmp;
	double	*result;
	double	*ambient;

	ambient = get_ambient(effective_color, comps);
	tmp = add_tuple(ambient, diffuse);
	result = add_tuple(tmp, specular);
	free(ambient);
	free(tmp);
	free(diffuse);
	free(specular);
	return (result);
}

void	find_specular(t_light *light, t_comps *comps, 
			double *lightv, double **specular)
{
	double	*negative;
	double	*lightv_neg;
	double	*reflectv;
	double	reflect_dot_eye;
	double	factor;

	negative = allocate_tuple(-1, -1, -1, 0);
	lightv_neg = multiply_tuple_tuple(lightv, negative);
	reflectv = reflect(lightv_neg, comps->normalv);
	reflect_dot_eye = dot_product_tuple(reflectv, comps->eyev);
	if (reflect_dot_eye <= 0)
		*specular = allocate_tuple(0, 0, 0, 0);
	else
	{
		factor = pow(reflect_dot_eye, comps->obj->material->shininess);
		*specular = multiply_scalar(light->intensity, 
				comps->obj->material->specular * factor);
	}
	free (negative);
	free (lightv_neg);
	free (reflectv);
}

void	zeroed_diffuse_specular(double	**diffuse, double **specular)
{
	*diffuse = allocate_tuple(0, 0, 0, 0);
	*specular = allocate_tuple(0, 0, 0, 0);
}

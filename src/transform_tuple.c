/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_tuple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:43:24 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/14 18:31:55 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * (PI / 180.0));
}

double	radians_to_degrees(double radians)
{
	return (radians * (180.0 / PI));
}

double	*rotate_vector_x(double *vector, double angle)
{

}

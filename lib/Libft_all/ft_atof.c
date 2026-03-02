/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 22:01:11 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/02 13:27:48 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	handle_decimal(const char *str)
{
	double	frac;
	double	div;

	str ++;
	div = 10.0;
	frac = 0.0;
	while (*str >= '0' && *str <= '9')
	{
		frac += (*str - '0') / div;
		div *= 10.0;
		str++;
	}
	return (frac);
}

double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	double	frac;

	result = 0.0;
	sign = 1.0;
	frac = 0.0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1.0;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
		frac = handle_decimal(str);
	return ((result + frac) * sign);
}

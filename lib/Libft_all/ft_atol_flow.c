/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:16:13 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:16:23 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atol_m_one(const char *nptr, unsigned long *result, int *sign)
{
	size_t			i;
	unsigned long	num;
	unsigned long	neg;
	int				range;

	i = 0;
	num = 0;
	neg = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = 1;
		i++;
	}
	range = i;
	while (++range < 19 && nptr[i] >= '0' && nptr[i] <= '9')
		num = num * 10 + nptr[i++] - '0';
	*sign = 1;
	if (neg)
		*sign = -1;
	*result = num;
	return (i);
}

/*checks if atol get's an under- or overflow.
Long is out of rang (<LONG_MIN || >LONG_MAX) = true*/
bool	ft_atol_flow(const char *str)
{
	unsigned long	result;
	unsigned long	next;
	size_t			i;
	int				sign;

	result = 0;
	i = ft_atol_m_one(str, &result, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		next = str[i] - '0';
		if (sign == 1)
		{
			if (result > (__LONG_MAX__ - next) / 10)
				return (true);
		}
		else
		{
			if (result > ((unsigned long) __LONG_MAX__ + 1 - next) / 10)
				return (true);
		}
		result = result * 10 + next;
		i++;
	}
	return (false);
}

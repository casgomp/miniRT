/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:24:59 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:25:01 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_negativ_n(long long n, int *count, int *i, int start);

void	ft_putnum_p(long long n, int *count, int *i, int start)
{
	char	num;

	if (start == 0)
	{
		*i += 2;
		start = 1;
	}
	if (n < 0)
		ft_negativ_n(n, count, i, start);
	else
	{
		if (n > 9)
		{
			ft_putnum_p (n / 10, count, i, start);
			ft_putnum_p (n % 10, count, i, start);
		}
		else
		{
			num = n + '0';
			write (1, &num, 1);
			*count += 1;
		}
	}
}

static void	ft_negativ_n(long long n, int *count, int *i, int start)
{
	write (1, "-", 1);
	*count += 1;
	ft_putnum_p (-n, count, i, start);
}

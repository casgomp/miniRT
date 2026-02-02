/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:24:46 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:24:48 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_start(int *i, unsigned char *mode);

static void	ft_write(unsigned long n, unsigned char mode, char *hex,
				char *hex_up);

void	ft_puthex_p(unsigned long n, int *count, int *i, unsigned char mode)
{
	char	*hex;
	char	*hex_up;

	hex = "0123456789abcdef";
	hex_up = "0123456789ABCDEF";
	if (mode == 'x' || mode == 'X' || mode == 'p')
		ft_start(i, &mode);
	if (mode == 'x' + 1 || mode == 'X' + 1)
	{
		if (n > 15)
		{
			ft_puthex_p(n / 16, count, i, mode);
			ft_puthex_p(n % 16, count, i, mode);
		}
		else
		{
			ft_write(n, mode, hex, hex_up);
			*count += 1;
		}
	}
}

static void	ft_start(int *i, unsigned char *mode)
{
	*i += 2;
	*mode += 1;
}

static void	ft_write(unsigned long n, unsigned char mode, char *hex,
				char *hex_up)
{
	if (n <= 15 && mode == 'x' + 1)
		write (1, &hex[n], 1);
	else
		write (1, &hex_up[n], 1);
}

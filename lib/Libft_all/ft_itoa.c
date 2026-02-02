/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:21:47 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:21:50 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_mod(long nu, char *num, int i);

static int	ft_digits(int n);

char	*ft_itoa(int n)
{
	char			*num;
	int				i;
	long			nu;
	int				len;

	nu = n;
	len = ft_digits(nu);
	num = (char *)malloc(len * sizeof(char));
	if (!num)
		return (NULL);
	num[len - 1] = 0;
	i = len - 2;
	if (nu >= 0)
		ft_mod(nu, num, i);
	if (nu < 0)
	{
		num[0] = '-';
		ft_mod(-nu, num, i);
	}
	return (num);
}

static void	ft_mod(long nu, char *num, int i)
{
	if (nu == 0)
		num[0] = '0';
	while (nu > 0)
	{
		num[i] = nu % 10 + '0';
		nu = nu / 10;
		i--;
	}
}

static int	ft_digits(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	else if (n == 0)
		return (++count);
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:24:52 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:24:56 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	num;

	if (fd >= 0)
	{
		if (n == -2147483648)
			write (fd, "-2147483648", 11);
		else if (n < 0)
		{
			write (fd, "-", 1);
			ft_putnbr_fd(-n, fd);
		}
		else if (n < 10 || n == 0)
		{
			num = n + '0';
			write (fd, &num, 1);
		}
		else
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putnbr_fd(n % 10, fd);
		}
	}
	else
		return ;
}

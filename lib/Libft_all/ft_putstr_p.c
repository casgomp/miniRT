/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:25:08 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:25:10 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_p(const char *str, int *count, int *i, int mode)
{
	int	j;

	j = 0;
	if (str == NULL)
	{
		write (1, "(null)", 6);
		*count += 6;
	}
	else
	{
		while (str[j] && str[j] != '%')
			write(1, &str[j++], 1);
		*count += j;
	}
	if (mode == 1)
		*i += j;
	else if (mode == 2)
		*i += 2;
}

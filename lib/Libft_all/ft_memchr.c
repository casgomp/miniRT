/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:23:58 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:24:00 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	cha;

	i = 0;
	p = (unsigned char *) s;
	cha = c;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (p[i] == cha)
			return ((void *)s);
		else
		{
			i++;
			s++;
		}
	}
	return (NULL);
}

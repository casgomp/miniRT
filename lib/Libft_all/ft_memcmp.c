/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:24:03 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:24:06 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;
	int				sum;

	i = 0;
	p1 = (unsigned char *) s1;
	p2 = (unsigned char *) s2;
	sum = 0;
	if (n == 0)
		return (sum);
	while (p1[i] == p2[i] && i < n - 1)
		i++;
	sum = p1[i] - p2[i];
	return (sum);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:24:14 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:24:18 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tem;
	unsigned char	*p_dest;

	i = 0;
	p_dest = (unsigned char *)dest;
	tem = (unsigned char *)src;
	if (p_dest == tem || n == 0)
		return (dest);
	if (p_dest > tem)
		while (n-- > 0)
			p_dest[n] = tem[n];
	else
	{
		while (i < n)
		{
			p_dest[i] = tem[i];
			i++;
		}
	}
	return (dest);
}

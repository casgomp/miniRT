/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:25:53 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:25:55 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat( char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_try;

	i = 0;
	j = 0;
	if (size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	len_try = ft_strlen(src) + ft_strlen(dst);
	while (dst[j])
		j++;
	while (j < size - 1 && src[i])
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (len_try);
}

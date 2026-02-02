/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:26:18 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:26:20 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return (-(unsigned char) s2[i]);
	if (s1 && !s2)
		return ((unsigned char) s1[i]);
	while ((unsigned char) s1[i] == (unsigned char) s2[i]
		&& i < n - 1 && (s1[i] && s2[i] != 0))
	{
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:26:24 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:26:26 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!little[i])
		return ((char *) big);
	while (big[i])
	{
		while (big[i + j] == little[j] && i + j < len && little[j])
			j++;
		if (!little[j])
			return ((char *) &big[i]);
		else
		{
			j = 0;
			i++;
		}
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:25:48 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:25:50 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*new;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = (ft_strlen(s1) + (ft_strlen(s2)) + 1);
	new = (char *)malloc(len * sizeof(char));
	if (new == NULL)
		return (NULL);
	new[0] = '\0';
	ft_strlcat(new, s1, len);
	ft_strlcat(new, s2, len);
	return (new);
}

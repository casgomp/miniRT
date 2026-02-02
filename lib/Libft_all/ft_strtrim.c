/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:26:36 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:26:38 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = ft_strlen (s1) - 1;
	if (!set)
		return (ft_strdup (s1));
	if (!s1 || s1[0] == 0)
	{
		return (ft_strdup (""));
	}
	while (s1[i] && ft_strchr (set, s1[i]))
		i++;
	if (i > j)
		return (ft_strdup (""));
	while (ft_strchr (set, s1[j]))
		j--;
	new = (char *)malloc((j - i + 2) * sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, &s1[i], j - i + 2);
	return (new);
}

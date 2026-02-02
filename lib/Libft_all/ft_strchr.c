/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:25:24 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:25:26 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*p_s;
	unsigned char	ch;

	i = 0;
	p_s = (char *)s;
	ch = (unsigned char) c;
	if (ch == 0)
		return (&p_s[ft_strlen(p_s)]);
	while (p_s[i])
	{
		if (p_s[i] == ch)
			return (&p_s[i]);
		else
			i++;
	}
	return (NULL);
}

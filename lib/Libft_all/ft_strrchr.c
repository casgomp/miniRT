/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:26:30 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:26:32 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*p_s;
	unsigned char	ch;

	ch = (unsigned char) c;
	i = ft_strlen(s) - 1;
	p_s = (char *)s;
	if (ch == 0)
	{
		return (&p_s[ft_strlen(p_s)]);
	}
	while (i >= 0)
	{
		if ((unsigned)p_s[i] == ch)
			return (&p_s[i]);
		else
			i--;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_newline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:19:07 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/05 16:37:42 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim_newline(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (NULL);
	while (s[len] != '\0')
		len++;
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
	return (s);
}

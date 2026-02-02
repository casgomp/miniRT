/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:20:26 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:20:28 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if ((nmemb != 0 && size > SIZE_MAX / nmemb))
	{
		return (NULL);
	}
	p = malloc (size * nmemb);
	if (p == NULL)
	{
		return (NULL);
	}
	if (size * nmemb == 0)
		return (p);
	else
	{
		ft_bzero (p, (nmemb * size));
		return (p);
	}
}

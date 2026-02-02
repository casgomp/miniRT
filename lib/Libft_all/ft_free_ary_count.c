/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ary_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:20:37 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:20:40 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_ary_count(void **data, size_t count)
{
	size_t	i;

	i = 0;
	if (!data)
		return ;
	while (count > 0)
	{
		free(data[i++]);
		count--;
	}
	free(data);
	data = NULL;
}

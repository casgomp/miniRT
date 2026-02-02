/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_three_ary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:20:44 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:20:50 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_three_ary(void ***data, size_t count_i)
{
	size_t	i;
	size_t	j;

	if (!data)
		return ;
	i = -1;
	while (++i < count_i)
	{
		if (data[i])
		{
			j = 0;
			while (data[i][j])
				free(data[i][j++]);
			free(data[i]);
		}
	}
	free(data);
	data = NULL;
}

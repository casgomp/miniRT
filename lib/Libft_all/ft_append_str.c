/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 20:59:56 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/04 21:01:51 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_append_str(char **arr, char *new_str)
{
	char	**new_arr;
	int		len;
	int		i;

	len = 0;
	while (arr && arr[len])
		len++;
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[len] = new_str;
	new_arr[len + 1] = NULL;
	free(arr);
	return (new_arr);
}

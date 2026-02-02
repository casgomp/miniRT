/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:25:13 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:25:15 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_buffer(char **buffer, char *tmp)
{
	char	*joined;

	if (!*buffer)
		*buffer = ft_strdup(tmp);
	else
	{
		joined = ft_strjoin(*buffer, tmp);
		free(*buffer);
		*buffer = joined;
	}
}

/*Copies what it reads in the buffer and returns
how total_size of what was read*/
int	ft_read_pipe(int read_fd, char **result)
{
	char	tmp[1024];
	char	*buffer;
	long	size;
	size_t	total_size;

	buffer = ft_strdup("");
	size = 0;
	total_size = 0;
	while (1 && buffer)
	{
		size = read(read_fd, tmp, sizeof(tmp));
		if (size <= 0)
			break ;
		total_size += size;
		tmp[size] = '\0';
		fill_buffer(&buffer, tmp);
	}
	close(read_fd);
	if (size < 0)
		free(buffer);
	if (!buffer)
		buffer = NULL;
	*result = buffer;
	return (total_size);
}

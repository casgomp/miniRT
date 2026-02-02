/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:26:58 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:27:00 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_join(char *line, char *s2, char *mode);
static char	*ft_read(int fd, char *line, char *rest, char *buffer_text);
static char	*ft_cut(char *text, char *rest, char *buffer);

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE];
	char		*line;
	char		*buffer_text;

	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strchr(rest, '\n') != NULL)
	{
		line = ft_cut(NULL, rest, NULL);
		return (line);
	}
	line = NULL;
	if (rest[0] != '\0')
	{
		line = ft_join(line, rest, "f");
		rest[0] = '\0';
		if (!line)
			return (NULL);
	}
	buffer_text = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	line = ft_read(fd, line, rest, buffer_text);
	free (buffer_text);
	return (line);
}

static char	*ft_join(char *line, char *s2, char *mode)
{
	char	*temp;

	if (*mode == 'f')
		line = ft_strdup(s2);
	else if (*mode == 'b' || *mode == 'o')
	{
		if (!line)
		{
			line = ft_strdup(s2);
			return (line);
		}
		temp = ft_strdup(line);
		free (line);
		if (!temp)
			return (NULL);
		line = ft_strjoin(temp, s2);
		if (*mode == 'b')
			free (s2);
		free (temp);
	}
	if (!line)
		return (NULL);
	return (line);
}

static char	*ft_read(int fd, char *line, char *rest, char *buffer_text)
{
	int		bytes;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer_text, BUFFER_SIZE);
		if ((bytes < 0) || (bytes == 0 && !line))
		{
			free (line);
			return (NULL);
		}
		else if (bytes == 0)
			return (line);
		buffer_text[bytes] = 0;
		if (ft_strchr(buffer_text, '\n') != NULL)
			return (ft_cut (line, rest, buffer_text));
		else
			line = ft_join (line, buffer_text, "o");
		if (!line)
			return (NULL);
	}
	return (NULL);
}

static char	*ft_cut(char *text, char *rest, char *buffer)
{
	char	*temp;
	char	*new;
	int		len;

	len = 0;
	if (!buffer)
		temp = ft_strdup(rest);
	if (buffer)
		temp = ft_strdup(buffer);
	if (!temp)
		return (NULL);
	while (temp[len] != '\n')
		len++;
	ft_strlcpy(rest, ft_strchr(temp, '\n') + 1, BUFFER_SIZE);
	new = (char *)malloc((len + 2) * sizeof(char));
	if (!new)
	{
		free (temp);
		return (NULL);
	}
	ft_strlcpy(new, temp, len + 2);
	free (temp);
	if (text)
		new = ft_join (text, new, "b");
	return (new);
}

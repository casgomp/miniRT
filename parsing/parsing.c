/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:04:36 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/17 22:56:40 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	parse_identifier(char **data, t_world **scene, int id)
{
	if (ft_strcmp(data[0], "A") == 0)
		return (parse_ambient(data, scene, id));
	if (ft_strcmp(data[0], "C") == 0)
		return (parse_camera(data, scene, id));
	if (ft_strcmp(data[0], "L") == 0)
		return (parse_light(data, scene, id));
	if (ft_strcmp(data[0], "sp") == 0)
		return (parse_sphere(data, scene, id));
	if (ft_strcmp(data[0], "pl") == 0)
		return (parse_plane(data, scene, id));
	if (ft_strcmp(data[0], "cy") == 0)
		return (parse_cylinder(data, scene, id));
	return (print_error(2, "wrong or missing identifier\n"), 0);
}

static int	identifier_check(char *identifier_line, t_world **scene, int id)
{
	char	**identifier_data;
	int		res;

	identifier_data = ft_split(identifier_line, ' ');
	if (!identifier_data)
		return (perror(MALL_ERR), 0);
	res = parse_identifier(identifier_data, scene, id);
	ft_free_array(&identifier_data);
	return (res);
}

static int	is_empty_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	**read_lines(const char *filename)
{
	char	**lines;
	char	*line;
	int		fd;

	lines = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror(MALL_ERR), NULL);
	line = get_next_line(fd);
	while (line)
	{
		ft_trim_newline(line);
		if (!is_empty_line(line))
			lines = ft_append_str(lines, line);
		else
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

t_world	*parse_input(char *input, t_world *scene)
{
	char	**lines;
	int		i;

	lines = read_lines(input);
	if (!lines)
		return (NULL);
	i = 0;
	while (lines[i])
	{
		if (!identifier_check(lines[i], &scene, i))
			return (ft_free_array(&lines), NULL);
		i++;
	}
	return (ft_free_array(&lines), scene);
}

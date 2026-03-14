/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:04:36 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/14 14:38:48 by pecastro         ###   ########.fr       */
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

t_world	*parse_input(char *input, t_world *scene)
{
	char		**rd_lines;
	char		*line;
	int			fd;
	int			i;

	rd_lines = NULL;
	fd = open(input, O_RDONLY);
	if (fd < 0)
		return (perror(MALL_ERR), NULL);
	line = ft_trim_newline(get_next_line(fd));
	while (line)
	{
		rd_lines = ft_append_str(rd_lines, line);
		line = ft_trim_newline(get_next_line(fd));
	}
	i = 0;
	while (rd_lines && rd_lines[i])
	{
		if (!identifier_check(rd_lines[i], &scene, i))
			return (ft_free_array(&rd_lines)
				, close(fd), free(line), NULL);
		i ++;
	}
	return (close(fd), ft_free_array(&rd_lines), scene);
}
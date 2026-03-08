/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:04:36 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/08 12:17:53 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	parse_identifier(char **data, t_object **lst, int id)
{
	if (ft_strcmp(data[0], "A") == 0)
		return (parse_ambient(data, lst, id));
	if (ft_strcmp(data[0], "C") == 0)
		return (parse_camera(data, lst, id));
	if (ft_strcmp(data[0], "L") == 0)
		return (parse_light(data, lst, id));
	if (ft_strcmp(data[0], "sp") == 0)
		return (parse_sphere(data, lst, id));
	if (ft_strcmp(data[0], "pl") == 0)
		return (parse_plane(data, lst, id));
	if (ft_strcmp(data[0], "cy") == 0)
		return (parse_cylinder(data, lst, id));
	return (print_error(2, "wrong or missing identifier\n"), 0);
}

static int	identifier_check(char *identifier_line, t_object **lst, int id)
{
	char	**identifier_data;
	int		res;

	identifier_data = ft_split(identifier_line, ' ');
	if (!identifier_data)
		return (perror(MALL_ERR), 0);
	res = parse_identifier(identifier_data, lst, id);
	ft_free_array(&identifier_data);
	return (res);
}

void	free_object_list(t_object *lst)
{
	t_object	*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->transform)
			free_grid(lst->transform);
		if (lst->inverse)
			free_grid(lst->inverse);
		if (lst->rgb)
			free(lst->rgb);
		if (lst->scale)
			free(lst->scale);
		free(lst);
		lst = tmp;
	}
}

t_object	*parse_input(char *input, t_object *lst)
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
		if (!identifier_check(rd_lines[i], &lst, i))
			return (ft_free_array(&rd_lines)
				, close(fd), free(line), NULL);
		i ++;
	}
	return (close(fd), ft_free_array(&rd_lines), lst);
}

int	main(int argc, char **argv)
{
	t_object		*lst;

	if (argc != 2)
		return (write(2, "Error\nenter one argument only\n", 30), 1);
	if (!file_format_error(argv[1]))
		return (1);
	lst = NULL;
	lst = parse_input(argv[1], lst);
	print_object_list(lst);
	free_object_list(lst);
	return (0);
}

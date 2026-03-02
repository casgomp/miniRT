/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:04:36 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/02 20:48:26 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	file_format_error(char *filename)
{
	int		len;

	if (!filename || filename[0] == '.')
	{
		write(2, "Error\nHidden files are not allowed\n", 35);
		return (0);
	}

	len = ft_strlen(filename);
	if (len < 3 || ft_strcmp(filename + len - 3, ".rt") != 0)
	{
		write(2, "Error\nfile format <filename>.rt\n", 32);
		return (0);
	}

	return (1);
}


int	identifier_check(char *identifier_line)
{
	char	*error_msg;
	char	**identifier_data;

	error_msg = "wrong or missing identifier\n";
	identifier_data = ft_split(identifier_line, ' ');
	if (!identifier_data)
		return (perror(MALL_ERR), 0);
	if (ft_strcmp(identifier_data[0], "A") == 0)
	{
		if (!parse_ambient(identifier_data))
			return (ft_free_array(&identifier_data), 0);
	}
	else if (ft_strcmp(identifier_data[0], "C") == 0)
	{
		if (!parse_camera(identifier_data))
			return (ft_free_array(&identifier_data), 0);
	}
	else if (ft_strcmp(identifier_data[0], "L") == 0)
	{
		if (!parse_light(identifier_data))
			return (ft_free_array(&identifier_data), 0);
	}
	else if (ft_strcmp(identifier_data[0], "sp") == 0)
	{
		if (!parse_sphere(identifier_data))
			return (ft_free_array(&identifier_data), 0);
	}
	else if (ft_strcmp(identifier_data[0], "pl") == 0)
	{
		if (!parse_plane(identifier_data))
			return (ft_free_array(&identifier_data), 0);
	}
	else if (ft_strcmp(identifier_data[0], "cy") == 0)
	{
		if (!parse_cylinder(identifier_data))
			return (ft_free_array(&identifier_data), 0);
	}
	else
	{
		write(2, "Error\n", 6);
		write(2, error_msg, ft_strlen(error_msg));
		return (0);
	}
	ft_free_array(&identifier_data);
	return (1);
}

int main (int argc, char **argv)
{
	if (argc > 2)
	{
		write(2, "Error\nenter one argument only\n", 30);
		return (1);
	}
	/*if(!file_format_error(argv[1]))
		return (1);*/
	if (!identifier_check(argv[1]))
		return (1);
	printf("all good\n");
}

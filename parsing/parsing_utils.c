/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:04:31 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/10 13:09:35 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	print_error(int fd, const char *msg)
{
	write(fd, "Error\n", 6);
	if (msg)
		write(fd, msg, ft_strlen(msg));
	return (0);
}

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

double	*str_to_double(char *str, double i)
{
	double	*coordinates;
	char	**str_coordinates;

	coordinates = malloc(4 * sizeof(double));
	if (!coordinates)
		return (perror(MALL_ERR), NULL);
	str_coordinates = ft_split(str, ',');
	if (!str_coordinates)
		return (free(coordinates), perror(MALL_ERR), NULL);
	coordinates[0] = ft_atof(str_coordinates[0]);
	coordinates[1] = ft_atof(str_coordinates[1]);
	coordinates[2] = ft_atof(str_coordinates[2]);
	coordinates[3] = i;
	ft_free_array(&str_coordinates);
	return (coordinates);
}

double	*str_to_rgb(char *str, double i)
{
	double		*coordinates;
	char		**str_coordinates;

	coordinates = malloc(4 * sizeof(double));
	if (!coordinates)
		return (perror(MALL_ERR), NULL);
	str_coordinates = ft_split(str, ',');
	if (!str_coordinates)
		return (free(coordinates), perror(MALL_ERR), NULL);
	coordinates[0] = ft_atof(str_coordinates[0]) / 255;
	coordinates[1] = ft_atof(str_coordinates[1]) / 255;
	coordinates[2] = ft_atof(str_coordinates[2]) / 255;
	coordinates[3] = i;
	ft_free_array(&str_coordinates);
	return (coordinates);
}

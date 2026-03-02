/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:05:59 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/02 18:05:08 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	rgb_parse(char *rgb)
{
	char		**rgb_values;
	char		*err_msg;
	int			i;

	i = 0;
	rgb_values = ft_split(rgb, ',');
	if (!rgb_values)
		return (perror(MALL_ERR), 0);
	err_msg = "RGB format misconfigured ex: ""255,255,255""\n";
	if (ft_lst_strsize(rgb_values) != 3)
		return (print_error(2, err_msg));
	while (rgb_values[i])
	{
		if (ft_isnumber(rgb_values[i]))
		{
			if (ft_atoi(rgb_values[i]) > 255 || ft_atoi(rgb_values[i]) < 0)
				return (ft_free_array(&rgb_values),
					print_error(2, "RGB out of range ""0 to 255""\n"));
			else
				i ++;
		}
		else
			return (ft_free_array(&rgb_values),
				print_error(2, "RGB vlaue is not a number""\n"));
	}
	ft_free_array(&rgb_values);
	return (1);
}

int	parse_ambient(char **data)
{
	double		value;
	int			i;
	char		*err_msg_1;
	char		*err_msg_2;

	i = 0;
	err_msg_1 = "ambient light value out of range ""0 <= vlaue <= 1"" \n";
	err_msg_2 = "ambient light prams misconfigured <intensity> <RGB vlaue>\n";
	if (ft_lst_strsize(data) != 3)
		return (print_error(2, err_msg_2));
	value = ft_atof(data[1]);
	if (value < 0.0 || value > 1.0)
		return (print_error(2, err_msg_1));
	if (!rgb_parse(data[2]))
		return (0);
	return (1);
}

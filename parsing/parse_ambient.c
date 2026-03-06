/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:05:59 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/05 20:39:01 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*allocate_ambient(char **identifier, int id)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (perror(MALL_ERR), NULL);
	obj->object_id = id;
	obj->object_type = AMBIENT_LIGHT;
	obj->brightness = ft_atof(identifier[1]);
	obj->transform = NULL;
	obj->angle = 0;
	obj->rgb = str_to_int(identifier[2], 0);
	if (!obj->rgb)
		return (free(obj), NULL);
	obj->inverse = NULL;
	obj->next = NULL;
	return (obj);
}

int	parse_ambient(char **data, t_object **lst, int id)
{
	double		value;
	char		*err_msg_1;
	char		*err_msg_2;
	t_object	*new;

	err_msg_1 = "ambient light value out of range ""0 <= vlaue <= 1"" \n";
	err_msg_2 = "ambient light prams misconfigured <intensity> <RGB vlaue>\n";
	if (ft_lst_strsize(data) != 3)
		return (print_error(2, err_msg_2));
	if (!ft_isnumber(data[1]))
		return (print_error(2, "ambient value is not a number\n"));
	value = ft_atof(data[1]);
	if (value < 0.0 || value > 1.0)
		return (print_error(2, err_msg_1));
	if (!rgb_parse(data[2]))
		return (0);
	new = allocate_ambient(data, id);
	*lst = append_object_lst(lst, new);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:04:31 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/02 16:39:32 by aabdella         ###   ########.fr       */
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

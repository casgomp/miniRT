/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:59:47 by pecastro          #+#    #+#             */
/*   Updated: 2026/02/17 16:06:35 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int unique_checker(char *line)
{
    
}

int base_checker(char *line)
{
    if (!line)
        return (1);
    //traverse and find each unique identifier
    //keep track of identifiers so none are repeated.
}

int parse(int fd)
{
    char    *line;

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            return (close(fd), 0);
        if (!base_checker(line))
            break;//
        free (line);
    }
    if (line)
        free(line);
    return (close(fd), 1);
}
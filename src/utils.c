/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:52:57 by pecastro          #+#    #+#             */
/*   Updated: 2026/03/14 13:30:03 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	grid_cpy(double **dst, double src[100][100], int size)
{
	int i = 0;
	int j = 0;

	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			dst[i][j] = src[i][j];
			j ++;
		}
		i ++;
	}
}

//utils tuple
double  *multiply_matrix_tuple(double **m, double *t)
{
    double  *res;
    int     i;
    static int b = 1;

    res = malloc(sizeof(double) * 4);
    if (!res)
        return (NULL);
    i = -1;
    while (++i < 4)
    {
        res[i] = (m[i][0] * t[0]) +
                 (m[i][1] * t[1]) +
                 (m[i][2] * t[2]) +
                 (m[i][3] * t[3]);
    }
    b ++;
    return (res);
}

double  *multiply_tuple_tuple(double *t1, double *t2)
{
    double  *new;
    int     i;

    new = ft_calloc(4, sizeof(double));
    if (!new)
        return (NULL);
    i = -1;
    while (++i < 4)
        new[i] = t1[i] * t2[i];
    return (new);
}

int color_to_int(double *color_percent)
{
    int rgb;
    int i;
    int color;

    if (!color_percent)
        return (0);
    //store individual colors in standard 255 value range and correct when overflow.
    //use OR to put all rgb bits into color
    rgb = 0;
    color = 0;
    i = -1;
    while (++i < 3)
    {
        rgb = color_percent[i] * 255.99;
        if (rgb > 255)
            rgb = 255;
        else if (rgb < 0)
            rgb = 0;
        if (i < 2)
            rgb <<= (2 - i) * 8;
        color |= rgb;
    }
    return (color);
}

//create list utils
void	lstadd(t_object **lst, t_object *new)
{
	t_object	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = lstlast(*lst);
	last -> next = new;
}

t_object	*lstlast(t_object *lst)
{
	t_object	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while ((tmp -> next) != NULL)
		tmp = tmp -> next;
	return (tmp);
}

t_material	*init_material(double *color, double ambient, double specular, double shininess)//temporary util to initialize material (eventually done in parsing)
{
	t_material	*m;

	m = malloc(sizeof(t_material));
	if (!m)
		return (NULL);
	m->color = color;
	m->ambient = ambient;
	m->diffuse = 0.7;
	m->specular = specular;
	m->shininess = shininess;
	return (m);
}
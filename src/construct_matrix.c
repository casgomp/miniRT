/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:21:48 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/16 11:16:12 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*void	ft_swap(double *a, double *b) //i've put it in libft
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}*/

/*
double	**identity_mtrx(int size) //i've made the function simpler (see below)
{
	double	**imtrx;
	int		diag;
	int		i;
	int		j;

	imtrx = allocate_grid(size);
	if (!imtrx)
		return (NULL);
	i = -1;
	diag = -1;
	while (++i < size)
	{
		diag ++;
		j = -1;
		while (++j < size)
		{
			if (j == diag)
				imtrx[i][j] = 1;
		}
	}
	return (imtrx);
}*/

double	**identity_mtrx(int size)
{
	double	**imtrx;
	int		i;

	imtrx = allocate_grid(size);
	if (!imtrx)
		return (NULL);
	i = -1;
	while (++i < size)
		imtrx[i][i] = 1;
	return (imtrx);
}

double	**duplicate_grid(double **grid)
{
	int		i;
	int		j;
	int		size;
	double	**duplicate_grid;

	i = 0;
	size = grid_size(grid);
	duplicate_grid = allocate_grid(size);
	if (!duplicate_grid)
		return (NULL);
	while (duplicate_grid[i])
	{
		j = 0;
		while (j < size)
		{
			duplicate_grid[i][j] = grid[i][j];
			j ++;
		}
		i ++;
	}
	return (duplicate_grid);
}

double	**transpose_grid(double **tmtrx)
{
	int		i;
	int		j;
	int		size;
	double	**dup_matrix;

	i = 0;
	size = grid_size(tmtrx);
	dup_matrix = duplicate_grid(tmtrx);
	if (!dup_matrix)
		return (NULL);
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			ft_swap(&dup_matrix[i][j], &dup_matrix[j][i]);
			j ++;
		}
		i ++;
	}
	return (dup_matrix);
}

t_matrix	construct_matrix(double **grid)
{
	t_matrix	matrix;
	int			size;

	size = grid_size(grid);
	matrix.size = size;
	matrix.grid = duplicate_grid(grid);
	matrix.transpose = transpose_grid(grid);
	matrix.determinant = determinant(grid, size);
	matrix.inverse = inverse(grid, size);
	if (!matrix.grid || !matrix.inverse || !matrix.transpose)
		return ((t_matrix){0});
	return (matrix);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrix_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:21:48 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/13 20:46:37 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_swap(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

float	**duplicate_grid(float **grid)
{
	int		i;
	int		j;
	int		size;
	float	**duplicate_grid;

	i = 0;
	size = grid_size(grid);
	duplicate_grid = allocate_grid(size);
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

float	**transpose_grid(float **tmtrx)
{
	int		i;
	int		j;
	int		size;
	float	**dup_matrix;

	i = 0;
	size = grid_size(tmtrx);
	dup_matrix = duplicate_grid(tmtrx);
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

t_matrix	construct_matrix(float **grid)
{
	t_matrix	matrix;
	int			size;

	size = grid_size(grid);
	matrix.size = size;
	matrix.grid = grid;
	matrix.transpose = transpose_grid(grid);
	matrix.determinant = determinant(grid, size);
	matrix.inverse = inverse(grid, size);
	return (matrix);
}

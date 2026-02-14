/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inversion_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:40:41 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/14 16:42:02 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	**inverse(double **grid, int size)
{
	double	**invgrid;
	double	det;
	int		i;
	int		j;

	det = determinant(grid, size);
	if (det == 0)
		return (NULL);
	invgrid = allocate_grid(size);
	if (!invgrid)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			invgrid[j][i] = cofactor(grid, size, i,j) / det;
		}
	}
	return (invgrid);
}

double	**get_submatrix(double **mtrx, int size, int rowskip, int colskip)
{
	double	**submtrx;
	int		i;
	int		sub_i;
	int		j;
	int 	sub_j;

	if (!mtrx || rowskip >= size || colskip >= size)
		return (NULL);
	submtrx = allocate_grid(size - 1);
	if (!submtrx)
		return (NULL);
	i = 0;
	sub_i = 0;
	while (i < size)
	{
		j = 0;
		sub_j = 0;
		if (i == rowskip)
			i++;
		else
		{
			while (i != rowskip && j < size)
			{
				if (j != colskip)
					submtrx[sub_i][sub_j++] = mtrx[i][j];
				j++;
			}
			sub_i += (i != rowskip);
			i++;
		}
	}
	return (submtrx);
}

double	cofactor(double **mtrx, int size, int row, int col)
{
	double	**submtrx;
	double	det;
	int		sign;

	submtrx = get_submatrix(mtrx, size, row, col);
	det = determinant(submtrx, size - 1);
	free_grid(submtrx);
	sign = 1;
	if ((col + row) % 2 != 0)
		sign = -sign;
	return (det * sign);
}

double	determinant(double **grid, int size)
{
	int		col;
	double	det;

	if (size == 1)
		return (grid[0][0]);
	if (size == 2)
		return (grid[0][0] * grid[1][1] - grid[0][1] * grid[1][0]);
	col = 0;
	det = 0;
	while (col < size)
	{
		det += grid[0][col] * cofactor(grid, size, 0, col);
		col ++;
	}
	return (det);
}

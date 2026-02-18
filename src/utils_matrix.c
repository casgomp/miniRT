/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:16:55 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/18 10:06:42 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	**allocate_grid(int size)
{
	int		i;
	double	**grid;

	i = 0;
	grid = malloc((size + 1) * sizeof(double *));
	if (!grid)
		return (perror(MALL_ERR), NULL);
	grid[size] = NULL;
	while (i < size)
	{
		grid[i] = ft_calloc(size, sizeof(double));
		if (!grid[i])
		{
			while (i > 0)
			{
				i --;
				free(grid[i]);
			}
			free(grid);
			return (perror(MALL_ERR), NULL);
		}
		i ++;
	}
	return (grid);
}

int	grid_size(double **grid)
{
	int		rows;

	rows = 0;
	if (!grid)
		return (0);
	while (grid[rows] != NULL)
		rows++;
	return (rows);
}

void	print_grid(double **grid)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = grid_size(grid);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			printf("%8.2lf ", grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

static double	dot_product(int i, int j, double **grid_1, double **grid_2)
{
	double		result;
	int			size;
	int			k;

	k = 0;
	result = 0;
	size = grid_size(grid_1);
	while (k < size)
	{
		result += grid_1[i][k] * grid_2[k][j];
		k ++;
	}
	return (result);
}

double	**matrix_multiply(double **grid_1, double **grid_2)
{
	int			i;
	int			j;
	double		**result;
	int			size;

	i = 0;
	j = 0;
	size = grid_size(grid_1);
	result = allocate_grid(size);
	if (!result)
		return (NULL);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			result[i][j] = dot_product(i, j, grid_1, grid_2);
			j++;
		}
		i++;
	}
	return (result);
}

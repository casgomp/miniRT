/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:16:55 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/13 21:10:56 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	**allocate_grid(int size)
{
	int		i;
	float	**grid;

	i = 0;
	grid = malloc((size + 1) * sizeof(float *));
	if (!grid)
		return (perror(MALL_ERR), NULL);
	grid[size] = NULL;
	while (i < size)
	{
		grid[i] = ft_calloc(size, sizeof(float));
		if (!grid[i])
		{
			while (i > 0)
			{
				i --;
				free(grid[i]);
			}
			free(grid);
			return (NULL);
		}
		i ++;
	}
	return (grid);
}

int	grid_size(float **grid)
{
	int		rows;

	rows = 0;
	if(!grid)
		return (0);
	while (grid[rows] != NULL)
		rows++;
	return (rows);
}

void	print_grid(float **grid)
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
			printf("%8.2f", grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

static float	dot_product(int i, int j, float **grid_1, float **grid_2)
{
	float		result;
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

float	**matrix_multiply(float **grid_1, float **grid_2)
{
	int			i;
	int			j;
	float		**result;
	int			size;

	i = 0;
	j = 0;
	size = grid_size(grid_1);
	result = allocate_grid(size);
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

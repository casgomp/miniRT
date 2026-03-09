/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:11:34 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/09 17:43:52 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_grid(double **grid)
{
	int	i;
	int	size;

	i = 0;
	size = grid_size(grid);
	while (i < size)
	{
		free(grid[i]);
		i ++;
	}
	free(grid);
	grid = NULL;
}

void	free_matrix(t_matrix *matrix)
{
	free_grid(matrix->grid);
	free_grid(matrix->transpose);
	free_grid(matrix->inverse);
	matrix -> grid = NULL;
	matrix -> transpose = NULL;
	matrix -> inverse = NULL;
}

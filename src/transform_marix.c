/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_marix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:43:57 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/15 17:00:45 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	**rotation_z(double r)
{
	double		**grid;
	const int	size = 4;
	int			i;

	grid = identity_mtrx(size);
	if (!grid)
		return (NULL);
	i = -1;
	while (++i < size - 2)
	{
		grid[i][i] = cos(r);
		grid[i][size - 3 - i] = sin(r);
	}
	grid[0][1] = -grid[0][1];
	return (grid);
}

double	**rotation_y(double r)
{
	double		**grid;
	const int	size = 4;
	int			i;

	grid = identity_mtrx(size);
	if (!grid)
		return (NULL);
	i = -1;
	while (++i < size - 1)
	{
		if (i % 2 == 0)
		{
			grid[i][i] = cos(r);
			grid[i][size - 2 - i] = sin(r);
		}
	}
	grid[2][0] = -grid[2][0];
	return (grid);
}

double	**rotation_x(double r)
{
	double		**grid;
	const int	size = 4;
	int			i;

	grid = identity_mtrx(size);
	if (!grid)
		return (NULL);
	i = 0;
	while (++i < size - 1)
	{
		grid[i][i] = cos(r);
		grid[i][size - 1 - i] = sin(r);
	}
	grid[1][2] = -grid[1][2];
	return (grid);
}

double	**scaling(double *coord)
{
	double		**grid;
	const int	size = 4;
	int			i;

	grid = identity_mtrx(size);
	if (!grid)
		return (NULL);
	i = -1;
	while (++i < size - 1)
	{
		grid[i][i] = coord[i];
	}
	return (grid);
}

double	**translation(double *coord)
{
	double		**grid;
	const int	size = 4;
	int			i;

	grid = identity_mtrx(size);
	if (!grid)
		return (NULL);
	i = -1;
	while (++i < size - 1)
	{
		grid[i][size - 1] = coord[i];
	}
	return (grid);
}

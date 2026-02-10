/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_marix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:43:57 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/10 16:59:13 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	**allocate_matrix(int size)
{
	int		i;
	int		**matrix;

	i = 0;
	matrix = malloc(size * sizeof(int *));
	if (!matrix)
	{
		perror(MALL_ERR);
		return (NULL);
	}
	while (i < size)
	{
		matrix[i] = ft_calloc(size, sizeof(int));
		if (!matrix[i])
		{
			free(matrix);
			return (NULL);
		}
		i ++;
	}
	return (matrix);
}

void	free_matrix(t_matrix *matrix)
{
	int	i;
	int	size;

	i = 0;
	size = matrix -> size;
	while (i < size)
	{
		free(matrix->grid[i]);
		i ++;
	}
	free (matrix->grid);
	free (matrix);
	matrix = NULL;
}

void	print_matrix(t_matrix *matrix)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = matrix->size;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			printf("%5d", matrix->grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

static int	r_c_multiply(int i, int j, t_matrix *matrix_1, t_matrix *matrix_2)
{
	int		result;
	int		size;
	int		k;

	k = 0;
	result = 0;
	size = matrix_1->size;
	while (k < size)
	{
		result += matrix_1->grid[i][k] * matrix_2->grid[k][j];
		k ++;
	}
	return (result);
}

t_matrix	*matrix_multiply(t_matrix *matrix_1, t_matrix *matrix_2)
{
	int			i;
	int			j;
	t_matrix	*result;
	int			size;

	i = 0;
	j = 0;
	size = matrix_1 -> size;
	result = ft_calloc(1, sizeof(t_matrix));
	result->grid = allocate_matrix(size);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			result->grid[i][j] = r_c_multiply(i, j, matrix_1, matrix_2);
			j++;
		}
		i++;
	}
	result->size = size;
	return (result);
}

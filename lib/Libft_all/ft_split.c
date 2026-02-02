/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:25:19 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:25:21 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_start(size_t *j, size_t *i, int *n);

static size_t	ft_count_w(char const *s, char c);

static char		*ft_copy(char const *s, size_t start, size_t end);

static void		*ft_free(char **split, size_t j);

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	j;
	size_t	i;
	int		new_w;

	ft_start(&j, &i, &new_w);
	split = (char **)malloc(sizeof(char *) * (ft_count_w(s, c) + 1));
	if (!split)
		return (NULL);
	while (i <= ft_strlen(s) && ft_strlen(s) != 0)
	{
		if (s[i] != c && new_w < 0)
			new_w = i;
		else if ((s[i] == c || i == ft_strlen(s)) && new_w >= 0)
		{
			split[j] = ft_copy(s, new_w, i);
			if (!split[j])
				return (ft_free(split, j));
			new_w = -1;
			j++;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}

static void	ft_start(size_t *j, size_t *i, int *n)
{
	*j = 0;
	*i = 0;
	*n = -1;
}

static size_t	ft_count_w(char const *s, char c)
{
	size_t	i;
	size_t	count;
	int		new_w;

	i = 0;
	count = 0;
	new_w = 1;
	while (s[i])
	{
		if (s[i] == c)
			new_w = 1;
		else if (s[i] != c && new_w == 1)
		{
			count ++;
			new_w = 0;
		}
		i++;
	}
	return (count);
}

static char	*ft_copy(char const *s, size_t start, size_t end)
{
	size_t	i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = 0;
	return (word);
}

static void	*ft_free(char **split, size_t j)
{
	while (j > 0)
	{
		free(split[j]);
		j--;
	}
	free(split);
	return (NULL);
}

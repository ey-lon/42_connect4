/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:27:55 by abettini          #+#    #+#             */
/*   Updated: 2023/05/16 16:33:40 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_matlen(char **mat)
{
	int	y;

	y = 0;
	if (mat)
	{
		while (mat[y])
			y++;
	}
	return (y);
}

void	ft_free_mat(char **mat)
{
	int	y;

	if (mat)
	{
		y = 0;
		while (mat[y])
		{
			free(mat[y]);
			y++;
		}
		free(mat);
	}
}

char	**ft_mat_create(int max_x, int max_y)
{
	char	**mat;
	int		y;

	mat = malloc(sizeof(char *) * (max_y + 1));
	y = 0;
	while (y < max_y)
	{
		mat[y] = malloc(sizeof(char) * max_x + 1);
		y++;
	}
	return (mat);
}

void	ft_mat_fill(char **mat, int max_x, int max_y, char c)
{
	int		y;
	int		x;

	y = 0;
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			mat[y][x] = c;
			x++;
		}
		mat[y][x] = '\0';
		y++;
	}
	mat[y] = NULL;
}

char	**ft_matdup(char **mat)
{
	char	**clone;
	int		y;

	if (!mat)
		return (NULL);
	clone = malloc(sizeof(char *) * (ft_matlen(mat) + 1));
	y = 0;
	while (mat[y])
	{	
		clone[y] = ft_strdup(mat[y]);
		y++;
	}
	clone[y] = NULL;
	return (clone);
}

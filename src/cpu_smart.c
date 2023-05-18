/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_smart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:26:58 by abettini          #+#    #+#             */
/*   Updated: 2023/05/16 15:10:19 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect_4.h"

//rows------------------------------------------------------------------------
static int	ft_c4_cpu_row_check(char **mat, int max_marks, char c)
{
	int		x;
	int		y;
	int		max_x;
	int		check;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	max_x = ft_strlen(mat[0]) - 1;
	y = 0;
	while (mat[y])
	{
		check = 0;
		x = 0;
		while (mat[y][x])
		{
			if (mat[y][x] == c)
				check++;
			else
				check = 0;
			if (check >= max_marks - 1)
			{
				if (x < max_x && mat[y][x + 1] == FREE && (!mat[y + 1] || mat[y + 1][x + 1] != FREE))
					return (x + 1);
				else if (x - (max_marks - 2) > 0 && mat[y][x - (max_marks - 1)] == FREE && (!mat[y + 1] || mat[y + 1][x - (max_marks - 1)] != FREE))
					return (x - (max_marks - 1));
			}
			x++;
		}
		y++;
	}
	return (-1);
}

//columns---------------------------------------------------------------------
static int	ft_c4_cpu_column_check(char **mat, int max_marks, char c)
{
	int		x;
	int		y;
	int		max_y;
	int		check;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	x = 0;
	max_y = ft_matlen(mat) - 1;
	while (mat[0][x])
	{
		check = 0;
		y = max_y;
		while (y > 0)
		{
			if (mat[y][x] == c)
				check++;
			else
				check = 0;
			if (check >= max_marks - 1 && y > 0 && mat[y - 1][x] == FREE)
				return (x);
			y--;
		}
		x++;
	}
	return (-1);
}

//diagonal_1------------------------------------------------------------------
static int	ft_c4_cpu_diag1_check(char **mat, int max_marks, int x, char c)
{
	int	y;
	int	check;
	int max_x;
	int max_y;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	max_x = ft_strlen(mat[0]) - 1;
	max_y = ft_matlen(mat) - 1;
	check = 0;
	y = 0;
	while (mat[y] && mat[y][x])
	{
		if (mat[y][x] == c)
			check++;
		else
			check = 0;
		if (check >= max_marks - 1)
		{
			if (x < max_x && mat[y + 1] && mat[y + 1][x + 1] == FREE && (!mat[y + 2] || mat[y + 2][x + 1] != FREE))
				return (x + 1);
			if (x - (max_marks - 2) > 0 && y - (max_marks - 2) > 0 && mat[y - (max_marks - 1)][x - (max_marks - 1)] == FREE && (mat[y - (max_marks - 1) + 1][x - (max_marks - 1)] != FREE))
				return (x - (max_marks - 1));
		}
		y++;
		x++;
	}
	return (-1);
}

//diagonal_2------------------------------------------------------------------
static int	ft_c4_cpu_diag2_check(char **mat, int max_marks, int x, char c)
{
	int	y;
	int	check;
	int max_x;
	int max_y;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	max_x = ft_strlen(mat[0]) - 1;
	max_y = ft_matlen(mat) - 1;
	check = 0;
	y = 0;
	while (mat[y] && x >= 0)
	{
		if (mat[y][x] == c)
			check++;
		else
			check = 0;
		if (check >= max_marks - 1)
		{
			if (x > 0 && mat[y + 1] && mat[y + 1][x - 1] == FREE && (!mat[y + 2] || mat[y + 2][x - 1] != FREE))
				return (x - 1);
			if (x + (max_marks - 2) < max_x && y - (max_marks - 2) > 0 && mat[y - (max_marks - 1)][x + (max_marks - 1)] == FREE && (mat[y - (max_marks - 1) + 1][x + (max_marks - 1)] != FREE))
				return (x + (max_marks - 1));
		}
		y++;
		x--;
	}
	return (-1);
}

//diagonal_call---------------------------------------------------------------
static int	ft_c4_cpu_call_diag1_check(char **mat, int max_marks, char c)
{
	int	x;
	int	y;
	int max_x;
	int	temp;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	temp = -1;
	y = ft_matlen(mat) - max_marks;
	x = 0;
	while (temp < 0 && y > 0)
	{
		temp = ft_c4_cpu_diag1_check(&mat[y], max_marks, x, c);
		y--;
	}
	max_x = ft_strlen(mat[0]) - max_marks;
	while (temp < 0 && x <= max_x)
	{
		temp = ft_c4_cpu_diag1_check(mat, max_marks, x, c);
		x++;
	}
	return (temp);
}

static int	ft_c4_cpu_call_diag2_check(char **mat, int max_marks, char c)
{
	int	x;
	int	y;
	int	min_x;
	int	temp;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	temp = -1;
	y = ft_matlen(mat) - max_marks;
	x = ft_strlen(mat[0]) - 1;
	while (temp < 0 && y > 0)
	{
		temp = ft_c4_cpu_diag2_check(&mat[y], max_marks, x, c);
		y--;
	}
	min_x = max_marks - 1;
	while (temp < 0 && x >= min_x)
	{
		temp = ft_c4_cpu_diag2_check(mat, max_marks, x, c);
		x--;
	}
	return (temp);
}

//smart_move----------------------------------------------------------------------
int	ft_c4_cpu_smart_move(char **mat, int max_marks, char c)
{
	int	temp;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	temp = ft_c4_cpu_row_check(mat, max_marks, c) + 1;
	if (!temp)
		temp = ft_c4_cpu_column_check(mat, max_marks, c) + 1;
	if (!temp)
		temp = ft_c4_cpu_call_diag1_check(mat, max_marks, c) + 1;
	if (!temp)
		temp = ft_c4_cpu_call_diag2_check(mat, max_marks, c) + 1;
	return (temp);
}

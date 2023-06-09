/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:27:45 by abettini          #+#    #+#             */
/*   Updated: 2023/05/15 10:27:45 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect_4.h"

//rows------------------------------------------------------------------------

static char	ft_c4_row_check(char **mat, int max_marks)
{
	int		x;
	int		y;
	char	temp;
	int		check;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	y = 0;
	while (mat[y])
	{
		check = 0;
		x = 0;
		while (mat[y][x])
		{
			if (!check)
				temp = mat[y][x];
			if (temp != FREE)
			{
				if (mat[y][x] == temp)
					check++;
				else
				{
					check = 0;
					x--;
				}
				if (check == max_marks)
					return (temp);
			}
			x++;
		}
		y++;
	}
	return (0);
}

//columns---------------------------------------------------------------------

static char	ft_c4_column_check(char **mat, int max_marks)
{
	int		x;
	int		y;
	char	temp;
	int		check;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	x = 0;
	while (mat[0][x])
	{
		check = 0;
		y = 0;
		while (mat[y])
		{
			if (!check)
				temp = mat[y][x];
			if (temp != FREE)
			{
				if (mat[y][x] == temp)
					check++;
				else
				{
					check = 0;
					y--;
				}
				if (check == max_marks)
					return (temp);
			}
			y++;
		}
		x++;
	}
	return (0);
}

//diagonal_1------------------------------------------------------------------

static char	ft_c4_diag1_check(char **mat, int max_marks, int x)
{
	int		y;
	char	temp;
	int		check;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	check = 0;
	y = 0;
	while (mat[y] && mat[y][x])
	{
		if (!check)
			temp = mat[y][x];
		if (temp != FREE)
		{
			if (mat[y][x] == temp)
				check++;
			else
			{
				check = 0;
				x--;
				y--;
			}
			if (check == max_marks)
				return (temp);
		}
		y++;
		x++;
	}
	return (0);
}

//diagonal_2------------------------------------------------------------------

static char	ft_c4_diag2_check(char **mat, int max_marks, int x)
{
	int		y;
	char	temp;
	int		check;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	check = 0;
	y = 0;
	while (mat[y] && x >= 0)
	{
		if (!check)
			temp = mat[y][x];
		if (temp != FREE)
		{
			if (mat[y][x] == temp)
				check++;
			else
			{
				check = 0;
				x++;
				y--;
			}
			if (check == max_marks)
				return (temp);
		}
		y++;
		x--;
	}
	return (0);
}

//diagonal_call---------------------------------------------------------------

char	ft_c4_call_diag1_check(char **mat, int max_marks)
{
	int		x;
	int		y;
	int		max_x;
	char	temp;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	temp = 0;
	y = ft_matlen(mat) - 1;
	x = 0;
	while (!temp && y > 0)
	{
		temp = ft_c4_diag1_check(&mat[y], max_marks, x);
		y--;
	}
	max_x = ft_strlen(mat[0]) - max_marks;
	while (!temp && x <= max_x)
	{
		temp = ft_c4_diag1_check(mat, max_marks, x);
		x++;
	}
	return (temp);
}

char	ft_c4_call_diag2_check(char **mat, int max_marks)
{
	int		x;
	int		y;
	int		min_x;
	char	temp;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	temp = 0;
	y = ft_matlen(mat) - 1;
	x = ft_strlen(mat[0]) - 1;
	while (!temp && y > 0)
	{
		temp = ft_c4_diag2_check(&mat[y], max_marks, x);
		y--;
	}
	min_x = max_marks - 1;
	while (!temp && x >= min_x)
	{
		temp = ft_c4_diag2_check(mat, max_marks, x);
		x--;
	}
	return (temp);
}

//win_check------------------------------------------------------------------

char	ft_c4_win_check(char **mat, int max_marks)
{
	char	temp;

	if (!mat || !mat[0] || !mat[0][0])
		return (0);
	//rows------------------------------------------------------------------------
	temp = ft_c4_row_check(mat, max_marks);
	if (temp)
		return (temp);
	//columns---------------------------------------------------------------------
	temp = ft_c4_column_check(mat, max_marks);
	if (temp)
		return (temp);
	//diagonal_1------------------------------------------------------------------
	temp = ft_c4_call_diag1_check(mat, max_marks);
	if (temp)
		return (temp);
	//diagonal_2------------------------------------------------------------------
	temp = ft_c4_call_diag2_check(mat, max_marks);
	if (temp)
		return (temp);
	return (0);
}

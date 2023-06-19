/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:27:08 by abettini          #+#    #+#             */
/*   Updated: 2023/05/18 14:59:40 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect_4.h"

//CPU----------------------------------------------------------------------

static int	*ft_free_join(int *arr, int arr_size, int n)
{
	int		*new_arr;
	int		i;

	new_arr = malloc(sizeof(int) * (arr_size + 1));
	i = 0;
	while (i < arr_size)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = n;
	if (arr_size)
		free(arr);
	return (new_arr);
}

//CPU moves based on its previous move
static int	ft_c4_cpu_star(char **mat, int size, int column)
{
	int	y;
	int	x;

	x = column - 1;
	y = 0;
	while (mat[y][x] != CPU)
		y++;
	//right_check-------------------------
	if (x + 1 < size && mat[y][x + 1] == FREE && (!mat[y + 1] || mat[y + 1][x + 1] != FREE))
		column = (x + 1);
	//left_check--------------------------
	else if (x > 0 && mat[y][x - 1] == FREE && (!mat[y + 1] || mat[y + 1][x - 1] != FREE))
		column = (x - 1);
	//up_check----------------------------
	else if (y > 0 && mat[y - 1][x] == FREE)
		column = (x);
	//diag_top_right_check----------------
	else if (y > 0 && x + 1 < size && mat[y - 1][x + 1] == FREE && mat[y][x + 1] != FREE)
		column = (x + 1);
	//diag_top_left_check-----------------
	else if (y > 0 && x > 0 && mat[y - 1][x - 1] == FREE && mat[y][x - 1] != FREE)
		column = (x - 1);
	//diag_bottom_right_check-------------
	else if (mat[y + 1] && x + 1 < size && mat[y + 1][x + 1] == FREE && (!mat[y + 2] || mat[y + 2][x + 1] != FREE))
		column = (x + 1);
	//diag_bottom_left_check--------------
	else if (mat[y + 1] && x > 0 && mat[y + 1][x - 1] == FREE && (!mat[y + 2] || mat[y + 2][x - 1] != FREE))
		column = (x - 1);
	else
		column = -1;
	return (column + 1);
}

//CPU chooses a random free column
static int	ft_c4_cpu_rdm(char **mat, int size)
{
	int		*arr;
	int		arr_size;
	int		column;

	arr = NULL;
	arr_size = 0;
	column = 1;
	while (column < size)
	{
		if (ft_search_char_in_column_n(mat, FREE, column))
		{
			arr = ft_free_join(arr, arr_size, column);
			arr_size++;
		}
		column++;
	}
	if (arr_size)
	{
		column = arr[rand() % ((arr_size - 1) + 1)];
		free(arr);
		return (column);
	}
	return (0);
}

static int	ft_c4_cpu_check_move(char **mat, int column, int max_marks)
{
	char	**clone;
	int		temp;

	clone = ft_matdup(mat);
	ft_c4_move(clone, column, CPU);
	temp = ft_c4_cpu_smart_move(clone, max_marks, P1);
	if (!temp)
		temp = ft_c4_cpu_smart_move_2(clone, max_marks, P1);
	ft_free_mat(clone);
	return (temp);
}

int	ft_mlx_cpu_move(t_game *game, t_mlx *meta, char **mat, int size, int max_marks)
{
	int			temp;
	int			i;
	int			check;
	char		*strmove;

	check = 0;
	temp = 0;
	if (game->column)
	{
		temp = ft_c4_cpu_smart_move(mat, max_marks, CPU);
		if (!temp)
			temp = ft_c4_cpu_smart_move_2(mat, max_marks, CPU);
		if (!temp)
			temp = ft_c4_cpu_smart_move(mat, max_marks, P1);
		if (!temp)
			temp = ft_c4_cpu_smart_move_2(mat, max_marks, P1);
		if (temp)
			check = 1;
		if (!check)
		{
			temp = ft_c4_cpu_smart_move(mat, max_marks - 1, CPU);
			if (!temp || ft_c4_cpu_check_move(mat, temp, max_marks))
				temp = ft_c4_cpu_smart_move(mat, max_marks - 1, P1);
			if (!temp || ft_c4_cpu_check_move(mat, temp, max_marks))
				temp = ft_c4_cpu_star(mat, size, game->column);
		}
		//random
		if (!check)
		{
			i = 0;
			while ((!temp || ft_c4_cpu_check_move(mat, temp, max_marks)) && i < 3)
			{
				temp = ft_c4_cpu_rdm(mat, size);
				i++;
			}
		}
	}
	else
	{
		temp = size / 2 + (size % 2);
	}
	game->column = temp;
	
	strmove = ft_strjoin_c4("CPU: column ", game->column);
	ft_logadd_front(&meta->log, ft_lognew(strmove, '2'));
	// strmove = ft_strdup("It's your turn");
	// ft_logadd_front(&meta->log, ft_lognew(strmove, '1'));
	ft_print_log(game, game->meta, game->meta->log);
	ft_mlx_move(meta, mat, game->column, CPU);
	return (0);
}

//rand() % (MAX - MIN + 1) + MIN;
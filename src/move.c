/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:27:23 by abettini          #+#    #+#             */
/*   Updated: 2023/05/17 17:18:00 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect_4.h"

//movement-----------------------------------------------------------------

int	ft_c4_move(char **mat, int column, int player)
{
	if (!mat)
		return (1);
	if (!ft_search_char_in_column_n(mat, FREE, column))
		return (ft_printf("Column full.\n") * 0 + 1);
	else
		ft_put_char_in_column_n_at_last_pos(mat, player, column, FREE);
	return (0);
}

int	ft_mlx_move(t_mlx *meta, char **mat, int column, int player)
{
	if (!mat)
		return (1);
	if (!ft_search_char_in_column_n(mat, FREE, column))
		return (1);
	else
		ft_mlx_put_char_in_column_n_at_last_pos(meta, mat, player, column, FREE);
	return (0);
}

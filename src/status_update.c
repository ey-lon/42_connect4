/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:27:41 by abettini          #+#    #+#             */
/*   Updated: 2023/05/15 10:27:41 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect_4.h"

static void	ft_c4_move_update(int player, int cpu, t_opt *opt)
{
	if (cpu && player != P1)
		ft_printf("%sThe Computer chose:%s\n", opt->p_col[2], NOCOL);
	else
		ft_printf("%sPlayer %c chose:%s\n", opt->p_col[player - '0'], player, NOCOL);
}

//---------------------------------------------------------------------------------

static int	ft_c4_win_update(t_game *game, char winner)
{
	game->turn++;
	if (!winner && game->turn < game->opt->grid_width * game->opt->grid_height)
		return (0);
	else if (!winner)
		return (ft_printf("%sIt'a tie!%s\n", BLUE, NOCOL) * 0 + 3);
	else if (game->cpu && winner != P1)
		return (ft_printf("%sCPU wins!%s\n", game->opt->p_col[2], NOCOL) * 0 + CPU);
	else
		return (ft_printf("%sPlayer %c wins!%s\n", game->opt->p_col[winner - '0'], winner, NOCOL) * 0 + winner);
	return (0);
}

static int ft_win_print(t_game *game, char winner)
{
	int x;
	int y;

	y = 0;
	while (y < game->opt->grid_height)
	{
		x = 0;
		while (x < game->opt->grid_width)
		{
			if (game->mat[y][x] == winner)
			{
				if (!game->cpu || winner == P1)
					mlx_put_image_to_window(game->meta->mlx, game->meta->win, game->meta->imgs[winner - '0' + 4], x * game->meta->tex_width, (y + 1) * game->meta->tex_height);
				else if (winner != P1)
					mlx_put_image_to_window(game->meta->mlx, game->meta->win, game->meta->imgs[winner - '0' + 5], x * game->meta->tex_width, (y + 1) * game->meta->tex_height);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static int	ft_mlx_win_update(t_game *game, char winner)
{
	game->turn++;
	if (!winner && game->turn < game->opt->grid_width * game->opt->grid_height)
		return (0);
	else if (!winner)
	{
		ft_logadd_front(&game->meta->log, ft_lognew(ft_strdup("It's a TIE"), '3'));
		ft_print_log(game, game->meta, game->meta->log);
		return (3);
	}
	else if (game->cpu && winner != P1)
	{
		ft_win_print(game, winner);
		ft_logadd_front(&game->meta->log, ft_lognew(ft_strdup("CPU Wins!"), '2'));
		ft_print_log(game, game->meta, game->meta->log);
		//mlx_string_put(game->meta->mlx, game->meta->win, 5, game->meta->hight - 2, 0xFFFF0000, "============== CPU Wins! =============");
		return (2);
	}
	else if (winner != P1)
	{
		ft_win_print(game, winner);
		ft_logadd_front(&game->meta->log, ft_lognew(ft_strdup("Player 2 Wins!"), '2'));
		ft_print_log(game, game->meta, game->meta->log);
		//mlx_string_put(game->meta->mlx, game->meta->win, 5, game->meta->hight - 2, 0xFFFF0000, "============== Player 2 Wins! =============");
		return (2);
	}
	else
	{
		ft_win_print(game, winner);
		ft_logadd_front(&game->meta->log, ft_lognew(ft_strdup("Player 1 Wins!"), '1'));
		ft_print_log(game, game->meta, game->meta->log);
		//mlx_string_put(game->meta->mlx, game->meta->win, 5, game->meta->hight - 2, 0xFFFFFF14, "============== Player 1 Wins! =============");
		return (1);
	}
}

//---------------------------------------------------------------------------------

int	ft_c4_status_update(t_game *game, int player)
{
	int	status;

	if (!game->meta)
	{
		ft_c4_move_update(player, game->cpu, game->opt); //mettere log
		ft_c4_print_mat(game->mat, game->opt);
		status = ft_c4_win_update(game, ft_c4_win_check(game->mat, game->opt->max_marks));
	}
	else
	{
		status = ft_mlx_win_update(game, ft_c4_win_check(game->mat, game->opt->max_marks));
	}
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:26:51 by abettini          #+#    #+#             */
/*   Updated: 2023/05/19 10:36:10 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect_4.h"

static int	ft_c4_header(void)
{
	ft_printf("------------------------------\n");
	ft_printf("|  Connect 4                 |\n");
	ft_printf("|                            |\n");
	ft_printf("|  type 'exit' to quit       |\n");
	ft_printf("------------------------------\n");
	return (0);
}

static void	ft_c4_game_init(t_game *game, t_opt *opt, int cpu_status)
{
	game->opt = opt;
	game->turn = 0;
	game->status = 0;
	game->cpu = cpu_status;
	game->mat = ft_mat_create(opt->grid_width, opt->grid_height);
	ft_mat_fill(game->mat, opt->grid_width, opt->grid_height, FREE);
	ft_c4_header();
	ft_printf("GAME ON!\n");
	ft_c4_print_mat(game->mat, game->opt);
}

//PVE------------------------------------------------------------------------------
int	ft_c4_pve(t_opt *opt)
{
	t_game	game;
	char	*str;
	int		cpu_start;

	game.meta = NULL;
	srand(time(0));
	ft_c4_game_init(&game, opt, 1);
	cpu_start = rand() % 2;
	if (cpu_start)
	{
		ft_printf("%sCPU turn!%s\n", opt->p_col[2], NOCOL);
		ft_c4_cpu_move(game.mat, opt->grid_width, opt->max_marks);
		game.status = ft_c4_status_update(&game, CPU);
	}
	while (!game.status)
	{
		ft_printf("%sPlayer 1 turn!%s\n", opt->p_col[1], NOCOL);
		str = get_next_line(0);
		if (!ft_strncmp("exit\n", str, 5))
			game.status = ft_printf("You gave up!\n") * 0 + 1;

		else if (!ft_arg_check(str, 1, opt->grid_width))
		{
			if (!ft_c4_move(game.mat, ft_atoi(str), P1))
			{
				game.status = ft_c4_status_update(&game, P1);
				if (!game.status)
				{
					ft_printf("%sCPU turn!%s\n", opt->p_col[2], NOCOL);
					ft_c4_cpu_move(game.mat, opt->grid_width, opt->max_marks);
					game.status = ft_c4_status_update(&game, CPU);
				}
			}
		}
		else
			ft_printf("Invalid argument.\n");
		if (str)
			free(str);
	}
	ft_free_mat(game.mat);
	return (0);
}

//PVP------------------------------------------------------------------------------
int	ft_c4_pvp(t_opt *opt)
{
	t_game	game;
	char	*str;
	char	player;

	srand(time(0));
	ft_c4_game_init(&game, opt, 0);
	player = (rand() % 2) + 1 + '0';
	game.meta = NULL;
	while (!game.status)
	{
		ft_printf("%sPlayer %c turn!%s\n", opt->p_col[player - '0'], player, NOCOL);
		str = get_next_line(0);
		if (!ft_strncmp("exit\n", str, 5))
			game.status = (ft_printf("Game ended!\n") * 0 - 1);
		else if (!ft_arg_check(str, 1, opt->grid_width))
		{
			if (!ft_c4_move(game.mat, ft_atoi(str), player))
			{
				game.status = ft_c4_status_update(&game, player);
				if (!game.status)
				{
					if (player == P1)
						player = P2;
					else
						player = P1;
				}
			}
		}
		else
			ft_printf("Invalid argument.\n");
		if (str)
			free(str);
	}
	ft_free_mat(game.mat);
	return (0);
}

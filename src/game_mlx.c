/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:26:51 by abettini          #+#    #+#             */
/*   Updated: 2023/05/18 15:28:42 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect_4.h"

static void	ft_mlx_game_init(t_game *game, t_opt *opt, t_mlx *meta, int cpu_status)
{
	game->menu = 0;
	game->player = P1;
	game->opt = opt;
	game->meta = meta;
	game->turn = 0;
	game->status = 0;
	game->cpu = cpu_status;
	game->column = 0;
	game->mat = ft_mat_create(opt->grid_width, opt->grid_height);
	ft_mat_fill(game->mat, opt->grid_width, opt->grid_height, FREE);
	//ft_printf("GAME ON!\n");
}

//MOUSE----------------------------------------------------------------------
int	ft_mouse_win_pvp(int key_code, int x, int y, t_game *game)
{
	t_mlx *meta = game->meta;

	if (!game->menu)
	{
		//open menu
		if ((x > game->meta->width - 192 + 26 && x < game->meta->width - 26) && (y < game->meta->hight - 16 && y > game->meta->hight - 38))
		{
			game->menu = 1;
			mlx_put_image_to_window(game->meta->mlx, game->meta->win, game->meta->menu[0], game->meta->width - 192, game->meta->hight - 192);
			return (1);
		}
	}
	else
	{
		//switch to PVE 
		if ((x > game->meta->width - 192 + 26 && x < game->meta->width - 26) && (y < game->meta->hight - 143 && y > game->meta->hight - 181))
		{
			game->opt->gamemode = 0;
			ft_free_mat(game->mat);
			ft_logclear(&game->meta->log);
			ft_mlx_start(game->opt, game->meta);
			return (1);
		}
		//REPLAY
		else if ((x > game->meta->width - 192 + 26 && x < game->meta->width - 26) && (y < game->meta->hight - 98 && y > game->meta->hight - 136))
		{
			ft_free_mat(game->mat);
			ft_logclear(&game->meta->log);
			ft_mlx_start(game->opt, game->meta);
			return (1);
		}
		//EXIT
		else if ((x > game->meta->width - 192 + 26 && x < game->meta->width - 26) && (y < game->meta->hight - 52 && y > game->meta->hight - 91))
		{
			ft_terminate(game, 0);
			return (1);
		}
		//closes menu
		else if ((x > game->meta->width - 192 + 26 && x < game->meta->width - 26) && (y < game->meta->hight - 16 && y > game->meta->hight - 38))
		{
			game->menu = 0;
			ft_print_log(game, game->meta, game->meta->log);
			return (1);
		}
	}
	game->menu = 0;
	if (!game->status && key_code == 1)
	{
		meta->set = x / 64 + 1;
		if (meta->set > game->opt->grid_width)
			return (1);
		if (ft_mlx_move(meta, game->mat, meta->set, game->player))
			return (1);
		if (game->player == P1)
			ft_logadd_front(&meta->log, ft_lognew(ft_strjoin_c4("P1: column ", meta->set), '1'));
		else
			ft_logadd_front(&meta->log, ft_lognew(ft_strjoin_c4("P2: column ", meta->set), '2'));
		ft_print_log(game, game->meta, game->meta->log);
		game->status = ft_c4_status_update(game, game->player);
		if (game->player == P1)
			game->player = P2;
		else
			game->player = P1;
	}
	return (0);
}

int	ft_mouse_win_cpu(int key_code, int x, int y, t_game *game)
{
	t_mlx *meta = game->meta;
	t_opt *opt = game->opt;
	
	if (!game->menu)
	{
		//open menu
		if ((x > game->meta->width - 192 + 26 && x < game->meta->width - 26) && (y < game->meta->hight - 16 && y > game->meta->hight - 38))
		{
			game->menu = 1;
			mlx_put_image_to_window(game->meta->mlx, game->meta->win, game->meta->menu[1], game->meta->width - 192, game->meta->hight - 192);
			return (1);
		}
	}
	else
	{
		//switch to PVP
		if ((x > game->meta->width - 192 + 26 && x < game->meta->width - 26) && (y < game->meta->hight - 143 && y > game->meta->hight - 181))
		{
			game->opt->gamemode = 1;
			ft_free_mat(game->mat);
			ft_logclear(&game->meta->log);
			ft_mlx_start(game->opt, game->meta);
			return (1);
		}
		//REPLAY
		else if ((x > game->meta->width - 192 + 26 && x < game->meta->width - 26) && (y < game->meta->hight - 98 && y > game->meta->hight - 136))
		{
			ft_free_mat(game->mat);
			ft_logclear(&game->meta->log);
			ft_mlx_start(game->opt, game->meta);
			return (1);
		}
		//EXIT
		else if ((x > game->meta->width - 192 + 26 && x < game->meta->width - 26) && (y < game->meta->hight - 52 && y > game->meta->hight - 91))
		{
			ft_terminate(game, 0);
			return (1);
		}
		//closes menu
		else if ((x > game->meta->width - 192 + 26 && x < game->meta->width - 26) && (y < game->meta->hight - 16 && y > game->meta->hight - 38))
		{
			game->menu = 0;
			ft_print_log(game, game->meta, game->meta->log);
			return (1);
		}
	}
	game->menu = 0;
	if (!game->status && key_code == 1)
	{
		meta->set = x / 64 + 1;
		if (meta->set > opt->grid_width)
			return (1);
		if (ft_mlx_move(meta, game->mat, meta->set, P1))
			return (1);
		ft_logadd_front(&meta->log, ft_lognew(ft_strjoin_c4("You: column ", meta->set), '1'));
		ft_print_log(game, game->meta, game->meta->log);
		game->status = ft_c4_status_update(game, P1);
		if (!game->status)
		{
			// ft_logadd_front(&meta->log, ft_lognew(ft_strdup("It's CPU turn"), '2'));
			// ft_print_log(game, game->meta, game->meta->log);
			// ft_printf("%sCPU turn!%s\n", game->opt->p_col[2], NOCOL); fare loop
			ft_mlx_cpu_move(game, meta, game->mat, opt->grid_width, opt->max_marks);
			game->status = ft_c4_status_update(game, CPU);
		}
	}
	return (0);
}

//---------------------------------------------------------------------------
int	ft_terminate(t_game *game, int x)
{
	int i;

	ft_free_mat(game->mat);
	i = 0;
	while (game->meta->imgs[i])
	{
		mlx_destroy_image(game->meta->mlx, game->meta->imgs[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		mlx_destroy_image(game->meta->mlx, game->meta->logimg[i]);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		mlx_destroy_image(game->meta->mlx, game->meta->menu[i]);
		i++;
	}
	ft_logclear(&game->meta->log);
	mlx_destroy_window(game->meta->mlx, game->meta->win);
	mlx_destroy_display(game->meta->mlx);
	free(game->meta->mlx);
	if (!x)
		exit(0);
	return (0);
}

int	ft_x_terminate(t_game *game)
{
	ft_terminate(game, 0);
	return (0);
}


int	ft_key_hooks(int keycode, t_game *game)
{
	if (keycode == B_ESC || (game->status && keycode == 32))
		ft_terminate(game, 0);
	return (0);
}

//PRINT mark at the top following mouse pos
int	ft_print_top(t_game *game)
{
	int	x;
	int	y;
	int i;
	int j;

	mlx_mouse_get_pos(game->meta->mlx, game->meta->win, &x, &y);
	j = 0;
	while (j < game->meta->tex_width)
	{
		if (x > (game->meta->tex_width / 2))
			i = x + (game->meta->tex_width / 2);
		else
			i = game->meta->tex_width;
		while (i < game->meta->width)
		{
			mlx_pixel_put(game->meta->mlx, game->meta->win, i, j, 0x000000);
			i++;
		}
		j++;
	}
	j = 0;
	while (j < game->meta->tex_width)
	{
		if (x < game->meta->width - (game->meta->tex_width / 2))
			i = x - (game->meta->tex_width / 2);
		else
			i = game->meta->width - game->meta->tex_width;
		while (i > 0)
		{
			mlx_pixel_put(game->meta->mlx, game->meta->win, i, j, 0x000000);
			i--;
		}
		j++;
	}
	if (x > (game->meta->tex_width / 2) && x < game->meta->width - (game->meta->tex_width / 2))
		mlx_put_image_to_window(game->meta->mlx, game->meta->win, game->meta->imgs[game->player - '0' + 2], x - (game->meta->tex_width / 2), 0);
	else if (x <= (game->meta->tex_width / 2))
		mlx_put_image_to_window(game->meta->mlx, game->meta->win, game->meta->imgs[game->player - '0' + 2], 0, 0);
	else
		mlx_put_image_to_window(game->meta->mlx, game->meta->win, game->meta->imgs[game->player - '0' + 2], game->meta->width - game->meta->tex_width, 0);
	return (0);
}

int	ft_mlx_pve(t_opt opt, t_mlx *meta)
{
	t_game	game;
	int		cpu_start;

	if (!opt.gamemode)
	{
		srand(time(0));
		ft_mlx_game_init(&game, &opt, meta, 1);
		cpu_start = rand() % 2;
		if (cpu_start)
		{
			ft_logadd_front(&meta->log, ft_lognew(ft_strdup("CPU start!"), '2'));
			ft_print_log(&game, meta, meta->log);
			ft_mlx_cpu_move(&game, meta, game.mat, opt.grid_width, opt.max_marks);
			game.status = ft_c4_status_update(&game, CPU);
		}
		else
		{
			ft_logadd_front(&meta->log, ft_lognew(ft_strdup("You start!"), '1'));
			ft_print_log(&game, meta, meta->log);
		}
		mlx_mouse_hook(meta->win, ft_mouse_win_cpu, &game);
	}
	else
	{
		ft_mlx_game_init(&game, &opt, meta, 0);
		ft_logadd_front(&meta->log, ft_lognew(ft_strdup("P1 start!"), '1'));
		ft_print_log(&game, meta, meta->log);
		mlx_mouse_hook(meta->win, ft_mouse_win_pvp, &game);
	}
	mlx_hook(meta->win, 17, 0, ft_x_terminate, &game);
	mlx_hook(meta->win, 2, 1L << 0, ft_key_hooks, &game);
	mlx_loop_hook(game.meta->mlx, ft_print_top, &game);
	mlx_loop(meta->mlx);
	return (0);
}

//PVP------------------------------------------------------------------------------
/* int	ft_mlx_pvp(t_opt opt, t_mlx *meta)
{
	t_game	game;

	//srand(time(0));

	mlx_hook(meta->win, 17, 0, ft_terminate, &game);
	mlx_hook(meta->win, 2, 1L << 0, ft_key_hooks, &game);
	mlx_loop_hook(game.meta->mlx, ft_print_top, &game);
	mlx_loop(meta->mlx);
	return (0);
}
 */

//PVE------------------------------------------------------------------------------
/* int	ft_mlx_pve(t_opt opt, t_mlx *meta)
{
	t_game	game;
	int		cpu_start;

	srand(time(0));
	ft_mlx_game_init(&game, &opt, meta, 1);
	cpu_start = rand() % 2;
	if (cpu_start)
	{
		ft_logadd_front(&meta->log, ft_lognew(ft_strdup("CPU start!"), '2'));
		ft_print_log(&game, meta, meta->log);
		ft_mlx_cpu_move(&game, meta, game.mat, opt.grid_width, opt.max_marks);
		game.status = ft_c4_status_update(&game, CPU);
	}
	else
	{
		ft_logadd_front(&meta->log, ft_lognew(ft_strdup("You start!"), '1'));
		ft_print_log(&game, meta, meta->log);
	}
	mlx_hook(meta->win, 17, 0, ft_x_terminate, &game);
	mlx_hook(meta->win, 2, 1L << 0, ft_key_hooks, &game);
	mlx_mouse_hook(meta->win, ft_mouse_win_cpu, &game);
	mlx_loop_hook(game.meta->mlx, ft_print_top, &game);
	mlx_loop(meta->mlx);
	return (0);
}

//PVP------------------------------------------------------------------------------
int	ft_mlx_pvp(t_opt opt, t_mlx *meta)
{
	t_game	game;

	//srand(time(0));
	ft_mlx_game_init(&game, &opt, meta, 0);
	ft_logadd_front(&meta->log, ft_lognew(ft_strdup("P1 start!"), '1'));
	ft_print_log(&game, meta, meta->log);
	mlx_hook(meta->win, 17, 0, ft_x_terminate, &game);
	mlx_hook(meta->win, 2, 1L << 0, ft_key_hooks, &game);
	mlx_mouse_hook(meta->win, ft_mouse_win_pvp, &game);
	mlx_loop_hook(game.meta->mlx, ft_print_top, &game);
	mlx_loop(meta->mlx);
	return (0);
} */

//utils----------------------------------------------------------------------------
int	ft_mlx_put_char_in_column_n_at_last_pos(t_mlx *meta, char **mat, char c, int n, char pos)
{
	int	y;
	int	x;
	int len;

	len = ft_strlen(mat[0]);
	if (!mat || n < 1 || n - 1 > len)
		return (1);
	y = 0;
	x = n - 1;
	while (mat[y])
	{
		if (mat[y][x] == pos && (!mat[y + 1] || mat[y + 1][x] != pos))
		{
			mlx_put_image_to_window(meta->mlx, meta->win, meta->imgs[c - '0'], x * meta->tex_width, (y + 1) * meta->tex_height);
			mat[y][x] = c;
			return (0);
		}
		y++;
	}
	return (1);
}

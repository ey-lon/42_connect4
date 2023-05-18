/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:27:20 by abettini          #+#    #+#             */
/*   Updated: 2023/05/18 15:06:07 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect_4.h"

static void ft_mlx_init(t_opt *opt, t_mlx *meta)
{
	meta->tex_width = 64;
	meta->tex_height = 64;
	meta->log_all_w = 192;
	meta->log_main_h = 192;
	meta->log_othe_h = 64;
	meta->width = opt->grid_width * meta->tex_width + 192;
	meta->hight = (opt->grid_height + 1) * meta->tex_height;// + 14;
	meta->log = NULL;
	meta->set = -1;
	meta->mlx = mlx_init();
	meta->win = mlx_new_window(meta->mlx, meta->width, meta->hight, "connect4");
	meta->imgs[0] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/slot_empty_64.xpm", &meta->tex_width, &meta->tex_height);
	meta->imgs[1] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/slot_yellow_64.xpm", &meta->tex_width, &meta->tex_height);
	meta->imgs[2] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/slot_red_64.xpm", &meta->tex_width, &meta->tex_height);
	meta->imgs[3] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/x_yellow_64.xpm", &meta->tex_width, &meta->tex_height);
	meta->imgs[4] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/x_red_64.xpm", &meta->tex_width, &meta->tex_height);
	meta->imgs[5] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/slot_yellow_win_64.xpm", &meta->tex_width, &meta->tex_height);
	meta->imgs[6] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/slot_red_win_64.xpm", &meta->tex_width, &meta->tex_height);
	meta->imgs[7] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/slot_red_lose_64.xpm", &meta->tex_width, &meta->tex_height);
	meta->imgs[8] = NULL;
	meta->logimg[0] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/log_top.xpm", &meta->log_all_w, &meta->log_main_h);
	meta->logimg[1] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/log_mid.xpm", &meta->log_all_w, &meta->log_othe_h);
	meta->logimg[2] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/log_bot.xpm", &meta->log_all_w, &meta->log_othe_h);
	meta->menu[0] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/menu_pve.xpm", &meta->menu_w, &meta->menu_h);
	meta->menu[1] = mlx_xpm_file_to_image(meta->mlx,
		"imgs/menu_pvp.xpm", &meta->menu_w, &meta->menu_h);
}

static void ft_c4_opt_init(t_opt *opt, int x, int y)
{
	opt->gamemode = PVP;
	opt->max_marks = MAX_MARKS;
	opt->grid_width = x;
	opt->grid_height = y;
	opt->p_col[0] = NOCOL;
	opt->p_col[1] = YELLOW;
	opt->p_col[2] = RED;
	opt->p_symbol[0] = ' ';
	opt->p_symbol[1] = 'O';
	opt->p_symbol[2] = 'O';
}

static int ft_how_to(void)
{
	ft_printf("-----------------------------------------------\n");
	ft_printf("SYNOPSYS\n");
	ft_printf("\t./connect4 [columns] [rows] [graphics]\n");
	ft_printf("\nGRAPHICS:\n");
	ft_printf("\tmlx\t(fancy graphics)\n");
	ft_printf("\tnoob\t(play on terminal)\n");
	ft_printf("-----------------------------------------------\n");
	return (0);
}

int ft_mlx_start(t_opt *opt, t_mlx *meta)
{
	int y;
	int x;

	y = 0;
	ft_mlx_init(opt, meta);
	meta->set = -1;
	//meta->win = mlx_new_window(meta->mlx, meta->width, meta->hight, "connect4");
	while (y < opt->grid_height)
	{
		x = 0;
		while (x < opt->grid_width)
		{
			mlx_put_image_to_window(meta->mlx, meta->win, meta->imgs[0], x * meta->tex_width, (y + 1) * meta->tex_height);
			x++;
		}
		y++;
	}
	if (!opt->gamemode)
		ft_mlx_pve(*opt, meta);
	else
		ft_mlx_pvp(*opt, meta);
	return (0);
}

int	main(int ac, char **av)
{
	t_opt	opt;
	t_mlx	meta;

	if (ac == 1)
		return (ft_how_to() * 0 + 1);
	if (ac != 4)
		return (ft_printf("Invalid arguments\n") * 0 + 1);
	if (!ft_strncmp(av[3], "mlx", 4))
	{
		if (ft_arg_check(av[1], C_MIN, C_MAX_MLX) || ft_arg_check(av[2], R_MIN, R_MAX_MLX))
			return (ft_printf("Invalid size\n") * 0 + 2);

		ft_c4_opt_init(&opt, ft_atoi(av[1]), ft_atoi(av[2]));
		ft_mlx_start(&opt, &meta);
	}
	else if(!ft_strncmp(av[3], "noob", 5))
	{
		if (ft_arg_check(av[1], C_MIN, C_MAX) || ft_arg_check(av[2], R_MIN, R_MAX))
			return (ft_printf("Invalid size\n") * 0 + 2);
		ft_c4_opt_init(&opt, ft_atoi(av[1]), ft_atoi(av[2]));
		if (!PVP)
			ft_c4_pve(opt);
		else
			ft_c4_pvp(opt);
	}
	else
		return (ft_printf("Invalid arguments\n") * 0 + 1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_4.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:27:14 by abettini          #+#    #+#             */
/*   Updated: 2023/05/19 10:13:42 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT_4_H
# define CONNECT_4_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <time.h>
# include "../Libft/libft.h"
# include "../utils/utils.h"

# include "mlx.h"
# include "keynum.h"
# include <math.h>
# include <stdbool.h>

//PLAYERS-------------------------------
# define FREE '0'
# define P1 '1'
# define P2 '2'
# define CPU '2'

# define PVP 1
# define PVE 0

//PVP on/off----------------------------
# ifndef GAMEMODE
#  define GAMEMODE PVE
# endif

//LIMITS--------------------------------
# define MAX_MARKS 4
# define C_MIN 7
# define R_MIN 6
# define C_MAX 50
# define R_MAX 50
# define C_MAX_MLX 30
# define R_MAX_MLX 14

typedef struct  s_log {
    char         *l;
	int			 color;
    struct s_log *next;
}               t_log;

typedef struct s_opt
{
	int		gamemode;
	int 	grid_width;
	int		grid_height;
	int		max_marks;
	char	*p_col[3];
	char	p_symbol[3];
}	t_opt;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_log	*log;
	int		set;
	int		width;
	int		hight;
	void	*imgs[9];
	void	*logimg[3];
	void	*menu[2];
	int		menu_w;
	int		menu_h;
	int		log_all_w;
	int		log_main_h;
	int		log_othe_h;
	int		tex_width;
	int		tex_height;
}				t_mlx;

typedef struct s_game
{
	t_opt	*opt;
	t_mlx	*meta;
	char	**mat;
	int		cpu;
	int		status;
	int		turn;
	int		player;
	int		menu;
	int		column;
}	t_game;

//MAIN------------------------------------
int		ft_c4_pve(t_opt opt);
int		ft_c4_pvp(t_opt opt);
//movement--------------------------------
int		ft_c4_move(char **mat, int square, int player);
//CPU-------------------------------------
int		ft_c4_cpu_move(char **mat, int size, int max_marks);
int		ft_c4_cpu_smart_move(char **mat, int max_marks, char c);
int		ft_c4_cpu_smart_move_2(char **mat, int max_marks, char c);
//status_update---------------------------
char	ft_c4_win_check(char **mat, int max_marks);
int		ft_c4_status_update(t_game *game, int player);
//print_mat-------------------------------
void	ft_c4_print_mat(char **mat, t_opt *opt);

//GRAPHICS-------------------------------
int 	ft_mlx_start(t_opt *opt, t_mlx *meta);
int		ft_terminate(t_game *game, int x);
int		ft_mlx_put_char_in_column_n_at_last_pos(t_mlx *meta, char **mat, char c, int n, char pos);
int		ft_mlx_game(t_opt opt, t_mlx *meta);
int		ft_mlx_move(t_mlx *meta, char **mat, int column, int player);
int		ft_mlx_cpu_move(t_game *game, t_mlx *meta, char **mat, int size, int max_marks);
//int		ft_mlx_pvp(t_opt opt, t_mlx *meta);

//LOG-------------------------------------
t_log	*ft_lognew(char *l, int plr);
void	ft_logclear(t_log **log);
void	ft_logadd_front(t_log **log, t_log *new);
char	*ft_strjoin_c4(char const *s1, int column);
void	ft_print_log(t_game* game, t_mlx *meta, t_log *log);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <ggiannit@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:27:58 by abettini          #+#    #+#             */
/*   Updated: 2023/05/17 14:10:25 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../Libft/libft.h"

// COLORS------------------------------------

# define NOCOL "\e[0m"
# define BLACK "\e[1;30m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define BLUE "\e[1;34m"
# define PURPLE "\e[1;35m"
# define CYAN "\e[1;36m"
# define WHITE "\e[1;37m"

typedef struct s_pos
{
	int	x;
	int y;
}	t_pos;


//err_check-----------------------------
int		ft_err_check(char *str);
int		ft_arg_check(char *str, int min, int max);
//mat_fts---------------------------------
int		ft_matlen(char **mat);
void	ft_free_mat(char **mat);
char	**ft_mat_create(int max_x, int max_y);
void	ft_mat_fill(char **mat, int max_x, int max_y, char c);
char	**ft_matdup(char **mat);
//mat_chars-------------------------------
t_pos	ft_search_char(char **mat, char c);
int		ft_set_char_at_pos_n(char **mat, char c, int n);
int		ft_search_char_in_column_n(char **mat, char c, int n);
int		ft_put_char_in_column_n_at_last_pos(char **mat, char c, int n, char pos);

#endif
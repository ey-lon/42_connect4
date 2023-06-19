/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <ggiannit@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:27:28 by abettini          #+#    #+#             */
/*   Updated: 2023/05/17 15:50:36 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect_4.h"

static void ft_c4_print_line(int len, int k, char *color)
{
	int x;

	x = 0;
	if (k == 1)
		ft_printf("\t%s┌%s", color, NOCOL);
	else if (k == 2)
		ft_printf("\t%s└%s", color, NOCOL);
	else
		ft_printf("\t%s├%s", color, NOCOL);
	while (x < len)
	{
		if (x > 0 && x < len && k == 0)
			ft_printf("%s┼%s", color, NOCOL);
		else if (x > 0 && x < len && k == 1)
			ft_printf("%s┬%s", color, NOCOL);
		else if (x > 0 && x < len && k == 2)
			ft_printf("%s┴%s", color, NOCOL);
		ft_printf("%s───%s", color, NOCOL);
		x++;
	}
	if (k == 1)
		ft_printf("%s┐%s\n", color, NOCOL);
	else if (k == 2)
		ft_printf("%s┘%s\n", color, NOCOL);
	else
		ft_printf("%s┤%s\n", color, NOCOL);
}

static void	ft_c4_print_columns_n(int len)
{
	int	x;

	x = 0;
	ft_c4_print_line(len, 1, NOCOL);
	ft_printf("\t");
	while (x < len)
	{
		ft_printf("│");
		x++;
		if (x > 9)
			ft_printf("%s%-3d%s", GREEN, x, NOCOL);
		else
			ft_printf("%s %d %s", GREEN, x, NOCOL);
	}
	ft_printf("│\n");
	ft_c4_print_line(len, 2, NOCOL);
}

void	ft_c4_print_mat(char **mat, t_opt *opt)
{
	int	x;
	int	y;
	int len;

	(void)opt;
	if (!mat || !mat[0])
		return ;
	len = ft_strlen(mat[0]);
	ft_printf("\n");
	//ft_c4_print_columns_n(len);
	ft_c4_print_line(len, 1, BLUE);
	y = 0;
	while (mat[y])
	{
		if (y > 0)
			ft_c4_print_line(len, 0, BLUE);
		x = 0;
		ft_printf("\t");
		while (mat[y][x])
		{
			ft_printf("%s│%s", BLUE, NOCOL);
			if (mat[y][x] == FREE)
				ft_printf("   ");
			else if (mat[y][x] == P1)
				ft_printf("%s %c %s", opt->p_col[1], opt->p_symbol[1], NOCOL);
			else
				ft_printf("%s %c %s", opt->p_col[2], opt->p_symbol[2], NOCOL);
			x++;
		}
		ft_printf("%s│%s\n", BLUE, NOCOL);
		y++;
	}
	ft_c4_print_line(len, 2, BLUE);
	ft_c4_print_columns_n(len);
	ft_printf("\n");
}
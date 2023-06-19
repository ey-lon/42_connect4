/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:56:35 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/18 14:23:37 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect_4.h"

void	ft_print_log(t_game* game, t_mlx *meta, t_log *log)
{	int 	y;
	t_log	*tmp;

	mlx_put_image_to_window(meta->mlx, meta->win, meta->logimg[0], game->meta->width - 192, 64);
	for (y = 0; y < game->opt->grid_height - 4; y++)
		mlx_put_image_to_window(meta->mlx, meta->win, meta->logimg[1], game->meta->width - 192, 256 + (y * 64));
	mlx_put_image_to_window(meta->mlx, meta->win, meta->logimg[2], game->meta->width - 192, 256 + (y * 64));
	tmp = log;
	y = 104;
	while (tmp)
	{
		if (y > meta->hight - 64)
			break ;
		mlx_string_put(meta->mlx, meta->win, game->meta->width - 140 , y, tmp->color, tmp->l);
		y += 30;
        tmp = tmp->next;
	}
}

void	ft_logadd_front(t_log **log, t_log *new)
{
	new->next = *log;
	*log = new;
}

void	ft_logclear(t_log **log)
{
	t_log	*temp;

	temp = NULL;
	while (*log)
	{
		temp = (*log)->next;
        free((*log)->l);
        free(*log);
		(*log) = temp;
	}
}

t_log	*ft_lognew(char *l, int plr)
{
	t_log	*new;

	new = malloc(sizeof(t_log));
	if (!new)
		return (NULL);
	new->l = l;
    if (plr == P1)
        new->color = 0x00FFFF00;
    else if (plr == P2)
        new->color = 0x00FF0000;
    else
        new->color = 0x0000F0FF;
	new->next = NULL;
	return (new);
}

char	*ft_strjoin_c4(char const *s1, int column)
{
	char	*j_str;
    char    *s2 = ft_itoa(column);
	size_t	i;
	size_t	k;

	if (!s1)
		return (NULL);
	j_str = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (j_str == NULL)
		return (NULL);
	i = 0;
    k = 0;
	while (s1 && *s1)
		j_str[i++] = *s1++;
	while (s2 && s2[k])
		j_str[i++] = s2[k++];
	j_str[i] = '\0';
    free(s2);
	return (j_str);
}

/* 
void	ft_logiter(t_log *log, void (*f)(void *))
{
	while (log)
	{
		(*f)(log->l);
		log = log->next;
	}
}

t_log	*ft_loglast(t_log *log)
{
	if (log == NULL)
		return (log);
	while (log->next != NULL)
		log = log->next;
	return (log);
}

t_log	*ft_logmap(t_log *log, void *(*f)(void *), void (*del)(void *))
{	
	t_log	*new_log;
	t_log	*temp;

	new_log = NULL;
	while (log)
	{
		temp = ft_lognew((*f)(log->l));
		if (!temp)
			ft_logdelone(log, del);
		ft_logadd_back(&new_log, temp);
		log = log->next;
	}
	return (new_log);
}

int	ft_logsize(t_log *log)
{
	int	k;

	k = 0;
	while (log)
	{
		log = log->next;
		k++;
	}
	return (k);
}

void	ft_logadd_back(t_log **log, t_log *new)
{
	t_log	*last_node;

	if (*log == NULL)
		*log = new;
	else
	{
		last_node = ft_loglast(*log);
		last_node->next = new;
	}
} */
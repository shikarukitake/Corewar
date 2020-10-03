/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 15:04:06 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/10/03 16:41:38 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_players(t_player **players, int players_num)
{
	int id;

	id = 1;
	while (id <= players_num)
	{
		ft_strdel(&(players[-1 + (id)]->name));
		ft_strdel(&(players[-1 + (id)]->comment));
		ft_memdel((void **)&(players[-1 + (id)]->code));
		ft_memdel((void **)&players[-1 + (id)]);
		id++;
	}
}

void	free_cursors(t_cursor **list)
{
	t_cursor	*current;
	t_cursor	*delete;

	current = *list;
	while (current)
	{
		delete = current;
		current = current->next;
		ft_memdel((void **)&delete);
	}
	*list = NULL;
}

void		free_vi_ma(t_vm **vi_ma)
{
	free_players((*vi_ma)->players, (*vi_ma)->players_num);
	free_cursors(&((*vi_ma)->cursors));
	ft_memdel((void **)vi_ma);
}

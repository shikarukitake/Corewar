/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 23:06:26 by sdagger           #+#    #+#             */
/*   Updated: 2020/10/03 23:06:28 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add_cursor(t_cursor **list, t_cursor *new)
{
	if (new)
		new->next = *list;
	*list = new;
}

void	set_cursors(t_vm *vm)
{
	int			id;
	unsigned	pc;

	id = 1;
	pc = 0;
	while (id <= vm->players_num)
	{
		add_cursor(&(vm->cursors), init_cursor(vm->players[id - 1], pc));
		vm->cursors_num++;
		pc += MEM_SIZE / vm->players_num;
		id++;
	}
}

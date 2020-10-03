/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 16:29:48 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/10/03 16:30:08 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_cycle(ssize_t cycle)
{
	ft_printf("It is now cycle %zd\n", cycle);
}

void		log_pc_movements(unsigned char *arena, t_cursor *cursor)
{
	unsigned i;

	ft_printf("ADV %d (%0.4p -> %0.4p) ",
										cursor->step,
										cursor->pc,
										cursor->pc + cursor->step);
	i = 0;
	while (i < cursor->step)
	{
		ft_printf("%02x ", arena[calc_addr(cursor->pc + i)]);
		i++;
	}
	ft_printf("\n");
}

void	log_cursor_death(t_vm *vm, t_cursor *cursor)
{
	ft_printf("Process %d hasn't lived for %zu cycles (CTD %zd)\n",
												cursor->id,
												vm->cycles - cursor->last_live,
												vm->cycles_to_die);
}

void	log_cycles_to_die(ssize_t cycles_to_die)
{
	ft_printf("Cycle to die is now %zd\n", cycles_to_die);
}
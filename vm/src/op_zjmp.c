/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:17:29 by ablizniu          #+#    #+#             */
/*   Updated: 2020/10/03 16:18:58 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_zjmp(t_cursor *cursor, int addr)
{
	ft_printf("P %4d | zjmp %d %s\n",
									cursor->id,
									addr,
									(cursor->carry) ? "OK" : "FAILED");
}

void	op_zjmp(t_vm *vm, t_cursor *cursor)
{
	int addr;

	cursor->step += OP_CODE_LEN;
	addr = get_op_arg(vm, cursor, 1, TRUE);
	if (vm->log & OP_LOG)
		log_zjmp(cursor, addr);
}

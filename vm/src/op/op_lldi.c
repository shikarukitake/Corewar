/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:49:45 by ablizniu          #+#    #+#             */
/*   Updated: 2020/10/03 16:20:52 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_structs.h"

inline static void	log_lldi(t_cursor *cursor,
							int addr_1,
							int addr_2,
							int r_id)
{
	ft_printf("P %4d | lldi %d %d r%d\n", cursor->id, addr_1, addr_2, r_id);
	ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
											addr_1,
											addr_2,
											addr_1 + addr_2,
											cursor->pc + (addr_1 + addr_2));
}

void				op_lldi(t_vm *vm, t_cursor *cursor)
{
	int	addr_1;
	int	addr_2;
	int	r_id;

	cursor->step += OP_CODE_LEN + ARGS_CODE_LEN;
	addr_1 = get_op_arg(vm, cursor, 1, TRUE);
	addr_2 = get_op_arg(vm, cursor, 2, TRUE);
	r_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->reg[INDEX(r_id)] = bytecode_to_int32(vm->arena,
			cursor->pc + (addr_1 + addr_2), DIR_SIZE);
	cursor->step += REG_LEN;
	if (vm->log & OP_LOG)
		log_lldi(cursor, addr_1, addr_2, r_id);
}

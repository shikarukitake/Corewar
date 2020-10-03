/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:28:48 by ablizniu          #+#    #+#             */
/*   Updated: 2020/10/03 16:24:22 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_sti(t_cursor *cursor,
							int r_id,
							int addr_1,
							int addr_2)
{
	ft_printf("P %4d | sti r%d %d %d\n",
										cursor->id,
										r_id,
										addr_1,
										addr_2);
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
							addr_1,
							addr_2,
							addr_1 + addr_2,
							cursor->pc + ((addr_1 + addr_2) % IDX_MOD));
}

void				op_sti(t_vm *vm, t_cursor *cursor)
{
	int	r_id;
	int	value;
	int	addr_1;
	int	addr_2;

	cursor->step += OP_CODE_LEN + ARGS_CODE_LEN;
	r_id = get_byte(vm, cursor->pc, cursor->step);
	value = cursor->reg[-1 + (r_id)];
	cursor->step += REG_LEN;
	addr_1 = get_op_arg(vm, cursor, 2, TRUE);
	addr_2 = get_op_arg(vm, cursor, 3, TRUE);
	int_to_bytecode(vm->arena,
			(cursor->pc + ((addr_1 + addr_2) % IDX_MOD)), value, DIR_SIZE);
	if (vm->log & OP_LOG)
		log_sti(cursor, r_id, addr_1, addr_2);
}

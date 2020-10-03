/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:31:12 by ablizniu          #+#    #+#             */
/*   Updated: 2020/10/03 16:16:43 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_st(unsigned int cursor_id, int r_id, int addr)
{
	ft_printf("P %4d | st r%d %d\n", cursor_id, r_id, addr);
}

void				op_st(t_vm *vm, t_cursor *cursor)
{
	int	r_id;
	int	r_value;
	int	addr;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	r_id = get_byte(vm, cursor->pc, cursor->step);
	r_value = cursor->reg[-1 + (r_id)];
	cursor->step += REG_LEN;
	if (cursor->args_types[1] == T_REG)
	{
		addr = get_byte(vm, cursor->pc, cursor->step);
		cursor->reg[-1 + (addr)] = r_value;
		cursor->step += REG_LEN;
	}
	else
	{
		addr = bytecode_to_int_utils(vm->arena,
							cursor->pc + cursor->step, IND_SIZE);
		int_to_bytecode(vm->arena, cursor->pc + (addr % IDX_MOD),
							r_value, DIR_SIZE);
		cursor->step += IND_SIZE;
	}
	if (vm->log & OP_LOG)
		log_st(cursor->id, r_id, addr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:50:03 by ablizniu          #+#    #+#             */
/*   Updated: 2020/10/03 16:15:54 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_structs.h"

inline static void	log_sub(unsigned int cursor_id,
							int r1_id,
							int r2_id,
							int r3_id)
{
	ft_printf("P %4d | sub r%d r%d r%d\n", cursor_id, r1_id, r2_id, r3_id);
}

void				op_sub(t_vm *vm, t_cursor *cursor)
{
	int	r1_id;
	int	r2_id;
	int	r3_id;
	int	value;

	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
	r1_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->step += REG_LEN;
	r2_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->step += REG_LEN;
	value = cursor->reg[INDEX(r1_id)] - cursor->reg[INDEX(r2_id)];
	cursor->carry = (t_bool)(!value);
	r3_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->reg[INDEX(r3_id)] = value;
	cursor->step += REG_LEN;
	if (vm->log & OP_LOG)
		log_sub(cursor->id, r1_id, r2_id, r3_id);
}

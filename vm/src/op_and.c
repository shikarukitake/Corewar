/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:33:19 by ablizniu          #+#    #+#             */
/*   Updated: 2020/10/03 16:19:53 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	log_and(unsigned int cursor_id,
							int value_1,
							int value_2,
							int r_id)
{
	ft_printf("P %4d | and %d %d r%d\n", cursor_id, value_1, value_2, r_id);
}

void	op_and(t_vm *vm, t_cursor *cursor)
{
	int	value_1;
	int	value_2;
	int	value;
	int	r_id;

	cursor->step += OP_CODE_LEN + ARGS_CODE_LEN;
	value_1 = get_op_arg(vm, cursor, 1, TRUE);
	value_2 = get_op_arg(vm, cursor, 2, TRUE);
	value = value_1 & value_2;
	cursor->carry = (t_bool)(!value);
	r_id = get_byte(vm, cursor->pc, cursor->step);
	cursor->reg[-1 + (r_id)] = value;
	cursor->step += REG_LEN;
	if (vm->log & OP_LOG)
		log_and(cursor->id, value_1, value_2, r_id);
}

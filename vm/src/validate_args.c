/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 16:44:15 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/10/03 16:45:09 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool			is_arg_types_valid(t_cursor *cursor, t_op *op)
{
	int	i;

	i = 0;
	while (i < op->args_num)
	{
		if (!(cursor->args_types[i] & op->args_types[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool			is_register(t_vm *vm, int pc, int step)
{
	int8_t	r_id;

	r_id = get_byte(vm, pc, step);
	return (t_bool)(r_id >= 1 && r_id <= REG_NUMBER);
}

t_bool			is_args_valid(t_cursor *cursor, t_vm *vm, t_op *op)
{
	int				i;
	unsigned int	step;

	i = 0;
	step = (OP_CODE_LEN + (op->args_types_code ? ARGS_CODE_LEN : 0));
	while (i < op->args_num)
	{
		if ((cursor->args_types[i] == T_REG)
			&& !is_register(vm, cursor->pc, step))
			return (FALSE);
		step += step_size(cursor->args_types[i], op);
		i++;
	}
	return (TRUE);
}

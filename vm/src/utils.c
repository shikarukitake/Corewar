/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:33:19 by ablizniu          #+#    #+#             */
/*   Updated: 2020/10/03 17:12:04 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		bytecode_to_int_utils(const unsigned char *arena, int addr, int size)
{
	int		result;
	t_bool		sign;
	int			i;

	result = 0;
	sign = (t_bool)(arena[calc_addr(addr)] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((arena[calc_addr(addr + size - 1)] ^ 0xFF) << (i++ * 8));
		else
			result += arena[calc_addr(addr + size - 1)] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

void		int_to_bytecode(unsigned char *arena, int addr, int value,
						int size)
{
	char i;

	i = 0;
	while (size)
	{
		arena[calc_addr(addr + size - 1)] = (unsigned char)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

int		get_op_arg(t_vm *vm, t_cursor *cursor,
					unsigned char index, t_bool mod)
{
	t_op		*op;
	int		value;
	int		addr;

	op = &g_op[-1 + (cursor->op_code)];
	value = 0;
	if (cursor->args_types[-1 + (index)] & T_REG)
		value = cursor->reg[-1 + (get_byte(vm, cursor->pc, cursor->step))];
	else if (cursor->args_types[-1 + (index)] & T_DIR)
		value = bytecode_to_int_utils(vm->arena,
								cursor->pc + cursor->step,
								op->t_dir_size);
	else if (cursor->args_types[-1 + (index)] & T_IND)
	{
		addr = bytecode_to_int_utils(vm->arena,
								cursor->pc + cursor->step,
								IND_SIZE);
		value = bytecode_to_int_utils(vm->arena,
							cursor->pc + (mod ? (addr % IDX_MOD) : addr),
							DIR_SIZE);
	}
	cursor->step += step_size(cursor->args_types[-1 + (index)], op);
	return (value);
}

t_cursor	*duplicate_cursor(t_cursor *cursor, int addr)
{
	t_cursor	*new;
	int			i;

	addr = calc_addr(cursor->pc + addr);
	new = init_cursor(cursor->player, addr);
	i = 0;
	while (i < REG_NUMBER)
	{
		new->reg[i] = cursor->reg[i];
		i++;
	}
	new->carry = cursor->carry;
	new->last_live = cursor->last_live;
	return (new);
}

int		ft_abs(int number)
{
	if (number < 0)
		return (number * -1);
	else
		return (number);
}
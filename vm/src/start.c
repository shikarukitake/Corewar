/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 16:06:42 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/10/03 16:49:37 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	update_op_code(t_vm *vm, t_cursor *current)
{
	current->op_code = vm->arena[current->pc];
	if (vm->arena[current->pc] >= 0x01 && vm->arena[current->pc] <= 0x10)
		current->cycles_to_exec = g_op[-1 + (current->op_code)].cycles;
}

void	move_cursor(t_cursor *cursor)
{
	cursor->pc += cursor->step;
	cursor->pc = calc_addr(cursor->pc);
	cursor->step = 0;
	ft_bzero(cursor->args_types, 3);
}

void	do_op(t_cursor *cursor, t_vm *vm)
{
	t_op *op;

	if (cursor->cycles_to_exec == 0)
		update_op_code(vm, cursor);
	if (cursor->cycles_to_exec > 0)
		cursor->cycles_to_exec--;
	if (cursor->cycles_to_exec == 0)
	{
		op = NULL;
		if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
			op = &g_op[-1 + (cursor->op_code)];
		if (op)
		{
			parse_types_code(vm, cursor, op);
			if (is_arg_types_valid(cursor, op) && is_args_valid(cursor, vm, op))
				op->func(vm, cursor);
			else
				cursor->step += calc_step(cursor, op);
			if (vm->log & PC_MOVEMENT_LOG && cursor->step)
				log_pc_movements(vm->arena, cursor);
		}
		else
			cursor->step = OP_CODE_LEN;
		move_cursor(cursor);
	}
}

void		in_cycle(t_vm *vm)
{
	t_cursor *current;

	vm->cycles++;
	vm->cycles_after_check++;
	if (vm->log & CYCLE_LOG)
		log_cycle(vm->cycles);
	current = vm->cursors;
	while (current)
	{
		do_op(current, vm);
		current = current->next;
	}
}

void		start(t_vm *vm)
{
	while (vm->cursors_num)
	{
		if (vm->dump_cycle == vm->cycles)
		{
			print_arena(vm->arena, vm->dump_print_mode);
			exit(0);
		}
		if (vm->show_cycle > 0 && !(vm->cycles % vm->show_cycle))
		{
			print_arena(vm->arena, vm->show_print_mode);
			while (getchar() != '\n')
				;
		}
		in_cycle(vm);
		if (vm->cycles_to_die == vm->cycles_after_check
			|| vm->cycles_to_die <= 0)
			cycles_to_die_check(vm);
	}
}
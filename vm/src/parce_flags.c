/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 18:16:56 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/09/29 11:44:34 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_structs.h"

void	parse_dump(int *argc, char ***argv, t_vm *vm)
{
	if (!vm->dump_print_mode && *argc >= 2 && ft_isint(*(*argv + 1), TRUE))
	{
		if ((vm->dump_cycle = ft_atoi(*(*argv + 1))) < 0)
			vm->dump_cycle = -1;
		if (!ft_strcmp(**argv, "-d"))
			vm->dump_print_mode = 64;
		else
			vm->dump_print_mode = 32;
		(*argc) -= 2;
		(*argv) += 2;
	}
	else
		print_help();
}

void parce_vs(int *ac, char **av, t_vm *vi_ma) 
{
    vi_ma->vs = init_vs();//add init
	(*ac)--;
	(*av)++;
}

void parce_log(int *ac, char ***av, t_vm *vi_ma)
{
    if (*ac >= 2 && ft_isint(*(*av + 1), TRUE))
	{
		vi_ma->log = ft_atoi(*(*av + 1));
		(*ac) -= 2;
		(*av) += 2;
	}
	else
		print_help();
}

void	parse_show(int *argc, char ***argv, t_vm *vm)
{
	if (!vm->show_print_mode && *argc >= 2 && ft_isint(*(*argv + 1), TRUE))
	{
		if ((vm->show_cycle = ft_atoi(*(*argv + 1))) <= 0)
			vm->show_cycle = -1;
		if (!ft_strcmp(**argv, "-s"))
			vm->show_print_mode = 64;
		else
			vm->show_print_mode = 32;
		(*argc) -= 2;
		(*argv) += 2;
	}
	else
		print_help();
}

void	parse_aff(int *argc, char ***argv, t_vm *vm)
{
	vm->display_aff = TRUE;
	(*argc)--;
	(*argv)++;
}
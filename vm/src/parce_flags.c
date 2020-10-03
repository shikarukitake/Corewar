/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 18:16:56 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/10/03 16:55:05 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	parse_dump(int *argc, char ***argv, t_vm *vi_ma)
{
	if (!vi_ma->dump_print_mode && *argc >= 2 && check_integer(*(*argv + 1), TRUE))
	{
		if ((vi_ma->dump_cycle = ft_atoi(*(*argv + 1))) < 0)
			vi_ma->dump_cycle = -1;
		if (!ft_strcmp(**argv, "-d"))
			vi_ma->dump_print_mode = 64;
		else
			vi_ma->dump_print_mode = 32;
		(*argc) -= 2;
		(*argv) += 2;
	}
	else
		print_help();
}

void	parse_log(int *ac, char ***av, t_vm *vi_ma)
{
    if (*ac >= 2 && check_integer(*(*av + 1), TRUE))
	{
		vi_ma->log = ft_atoi(*(*av + 1));
		(*ac) -= 2;
		(*av) += 2;
	}
	else
		print_help();
}

void	parse_show(int *argc, char ***argv, t_vm *vi_ma)
{
	if (!vi_ma->show_print_mode && *argc >= 2 && check_integer(*(*argv + 1), TRUE))
	{
		if ((vi_ma->show_cycle = ft_atoi(*(*argv + 1))) <= 0)
			vi_ma->show_cycle = -1;
		if (!ft_strcmp(**argv, "-s"))
			vi_ma->show_print_mode = 64;
		else
			vi_ma->show_print_mode = 32;
		(*argc) -= 2;
		(*argv) += 2;
	}
	else
		print_help();
}

void	parse_aff(int *argc, char ***argv, t_vm *vi_ma)
{
	vi_ma->display_aff = TRUE;
	(*argc)--;
	(*argv)++;
}
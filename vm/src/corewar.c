/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 15:17:04 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/10/03 16:59:45 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	main(int ac, char **av)
{
	t_vm	*vi_ma;

	if (ac > 1)
	{
		args_parce(ac, av, (vi_ma = init_vm()));
		init_arena(vi_ma);
		set_cursors(vi_ma);
		print_intro(vi_ma->players, vi_ma->players_num);
		start(vi_ma);
		print_winner(vi_ma);
		free_vi_ma(&vi_ma);
	}
	else
	{
		err_func();
		print_help();
	}
	return (0);
}

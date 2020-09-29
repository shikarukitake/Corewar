/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 18:16:56 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/09/20 18:30:43 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_structs.h"

void parce_dump(int ac, char **av, t_vm *vi_ma) 
{
    
}

void parce_vs(int *ac, char **av, t_vm *vi_ma) 
{
    vi_ma->vs = init_vs();//add init
	(*ac)--;
	(*av)++;
}

void parce_log(int ac, char **av, t_vm *vi_ma)
{
    
}

void parce_dump(int ac, char **av, t_vm *vi_ma)
{
    
}
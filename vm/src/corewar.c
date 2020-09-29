/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 15:17:04 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/09/20 17:32:13 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar_structs.h"

int main(int ac, char **av)
{
    t_vm *vi_ma;
    
    if (ac > 1)
    {
        args_parce(ac, **av, (vi_ma = init_vm()));
    }
    else
        err_func();

    return (0);
}
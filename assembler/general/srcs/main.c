/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 12:36:51 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/27 16:10:18 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	t_asm	*sasm;

	sasm = error_f(NULL, 1);
	if (ac != 2)
		error_f(USAGE, 0);
	read_file(sasm, av[1]);
	process_file(sasm);
	write_file(sasm, av[1]);
	free_asm(sasm);
	exit(0);
	return (0);
}

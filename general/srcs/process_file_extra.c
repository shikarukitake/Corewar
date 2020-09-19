/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:45:33 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/15 20:52:46 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		only_digit(t_asm *sasm, char *row)
{
	int		i;

	i = sasm->start;
	while (i != sasm->i)
	{
		if (!ft_isdigit(row[i]))
			return (0);
		i++;
	}
	return (1);
}

int		is_register(t_asm *sasm, char *row)
{
	if (row[sasm->start] == 'r')
	{
		if (sasm->i - sasm->start == 3)
		{
			if (row[sasm->start + 1] == '1'
				&& row[sasm->start + 2] >= '1'
				&& row[sasm->start + 2] <= '6')
				return (1);
		}
		else if (sasm->i - sasm->start == 2)
		{
			if (row[sasm->start + 1] >= '1'
				&&row[sasm->start + 1] <= '9')
				return (1);
		}
	}
	return (0);
}


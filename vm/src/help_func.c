/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 17:35:53 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/09/20 18:37:03 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELP_FUNC_H
# define HELP_FUNC_H 

# include "corewar_structs.h"

t_bool	check_tab(char c)
{
	if (c == '\n' || c == '\t' || c == ' '
			|| c == '\v' || c == '\f' || c == '\r')
            return (TRUE);
    return (FALSE);
}

t_bool	check_integer(const char *str, t_bool strict)
{
	unsigned int	result;
	unsigned int	border;
	int				i;
	int				sign;
	int				digits;

	result = 0;
	digits = 0;
	border = (unsigned int)(FT_INT_MAX / 10);
	i = 0;
	while (!strict && check_tab(str[i]))
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) && ++digits)
	{
		if (((result > border || (result == border && (str[i] - '0') > 7))
				&& sign == 1)
			|| ((result > border || (result == border && (str[i] - '0') > 8))
				&& sign == -1))
			return (FALSE);
		result = result * 10 + (str[i++] - '0');
	}
	return (!str[i] && digits);
}

t_player	*find_player(t_player *players_l, int id)
{
	t_player *player;

	player = NULL;
	if (id >= 1 && id <= MAX_PLAYERS)
	{
		player = players_l;
		while (player)
		{
			if (player->id == id)
				return (player);
			player = player->next;
		}
	}
	return (player);
}

#endif
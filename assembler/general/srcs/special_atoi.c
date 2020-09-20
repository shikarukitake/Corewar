/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:31:37 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/20 14:38:04 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
# define FT_ULONG_MAX	((unsigned long)(~0L))
# define FT_LONG_MAX	((long)(FT_ULONG_MAX >> 1))

static int			check_tab(char c)
{
	return (c == '\n' || c == '\t' || c == ' '
			|| c == '\v' || c == '\f' || c == '\r');
}

int32_t		ft_atoi32(const char *str)
{
	unsigned long	result;
	unsigned long	border;
	size_t			i;
	int				sign;

	result = 0;
	border = (unsigned long)(FT_LONG_MAX / 10);
	i = 0;
	while (check_tab(str[i]))
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		if ((result > border || (result == border && (str[i] - '0') > 7))
			&& sign == 1)
			return (-1);
		else if ((result > border || (result == border && (str[i] - '0') > 8))
				 && sign == -1)
			return (0);
		result = result * 10 + (str[i++] - '0');
	}
	return ((int32_t)(result * sign));
}

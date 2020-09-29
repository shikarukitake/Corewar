/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_some.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:38:39 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 16:39:03 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_whitespace(int c)
{
	return (c == '\t' ||
			c == '\v' ||
			c == '\f' ||
			c == '\r' ||
			c == ' ');
}

int		is_delimiter(int c)
{
	return (c == '\0'
			|| c == '\n'
			|| is_whitespace(c)
			|| c == COMMAND_CHAR
			|| c == '\"'
			|| c == DIRECT_CHAR
			|| c == SEPARATOR_CHAR
			|| c == COMMENT_CHAR
			|| c == ALT_COMMENT_CHAR);
}

void	skip_whitespace(t_asm *sasm, char *row)
{
	while (is_whitespace(row[sasm->i]))
		sasm->i++;
}

void	skip_comment(t_asm *sasm, char *row)
{
	if (row[sasm->i] == COMMENT_CHAR
		|| row[sasm->i] == ALT_COMMENT_CHAR)
		while (row[sasm->i] && row[sasm->i] != '\n')
			sasm->i++;
}

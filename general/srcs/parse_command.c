/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 18:28:08 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/14 19:09:09 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse_command(t_asm *sasm, char *row)
{
	int		start;
	t_token	*token;

	start = ++(sasm->i);
	while (row[sasm->i] && ft_strchr(LABEL_CHARS, row[sasm->i]))
		sasm->i++;
	if ((sasm->i - start) && is_whitespace(row[sasm->i]))
	{
		token = init_token(sasm, COMMAND);
		token->content = ft_strsub(row, start, sasm->i - start);
		add_token(sasm, token);
	}
	else
		error_f("Lexical error at", 0);
}
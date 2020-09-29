/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_some.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 12:37:03 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 16:38:10 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse_indirect(t_asm *sasm, char *row)
{
	sasm->start = ++sasm->i;
	if (row[sasm->i] == '-')
		sasm->i++;
	while (row[sasm->i] && ft_strchr(LABEL_CHARS, row[sasm->i]))
		sasm->i++;
	if ((sasm->i - sasm->start) && is_delimiter(row[sasm->i]))
		parse_chars_type(sasm, row, INDIRECT_LABEL);
	else
		error_f("lexico", 2);
}

void	parse_indirect_num(t_asm *sasm, char *row)
{
	sasm->start = sasm->i++;
	while (row[sasm->i] && ft_isdigit(row[sasm->i]))
		sasm->i++;
	if ((sasm->i - (sasm->start + 1)) && is_delimiter(row[sasm->i]))
		parse_chars_type(sasm, row, INDIRECT);
	else
		error_f("lexico", 2);
}

void	parse_token(t_asm *sasm, char *row)
{
	if (row[sasm->i] == SEPARATOR_CHAR)
		parse_separator(sasm);
	else if (ft_strchr(LABEL_CHARS, row[sasm->i]))
		parse_chars(sasm, row);
	else if (row[sasm->i] == DIRECT_CHAR)
		parse_direct(sasm, row);
	else if (row[sasm->i] == COMMAND_CHAR)
		parse_command(sasm, row);
	else if (row[sasm->i] == '\n')
		parse_newline(sasm);
	else if (row[sasm->i] == '"')
		parse_string(sasm, row);
	else if (row[sasm->i] == ':')
		parse_indirect(sasm, row);
	else if (row[sasm->i] == '-')
		parse_indirect_num(sasm, row);
	else
		error_f("undefined ch when parsing", 2);
}

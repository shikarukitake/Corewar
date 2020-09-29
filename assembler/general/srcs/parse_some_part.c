/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_some_part.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:37:27 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 16:38:10 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse_chars_type(t_asm *sasm, char *row, t_ctype type)
{
	t_token	*token;

	token = init_token(sasm, type);
	token->content = ft_strsub(row, sasm->start, sasm->i - sasm->start);
	if (type == DIRECT && !ft_strisonlydigit(token->content))
		error_token("DIRECT token have wrong characters", token);
	if (token->content == NULL)
		error_f("ft_strsub malloc", 0);
	add_token(sasm, token);
}

void	parse_chars(t_asm *sasm, char *row)
{
	sasm->start = sasm->i;
	while (row[sasm->i] && ft_strchr(LABEL_CHARS, row[sasm->i]))
		sasm->i++;
	if ((sasm->i - sasm->start) && row[sasm->i] == LABEL_CHAR)
		parse_label(sasm, row);
	else if ((sasm->i - sasm->start) && is_delimiter(row[sasm->i]))
	{
		if (only_digit(sasm, row))
			parse_chars_type(sasm, row, INDIRECT);
		else if (is_register(sasm, row))
			parse_chars_type(sasm, row, REGISTER);
		else
			parse_chars_type(sasm, row, OPERATOR);
	}
	else
		error_f("lexico", 2);
}

void	parse_direct(t_asm *sasm, char *row)
{
	t_ctype	type;

	sasm->start = ++sasm->i;
	if (row[sasm->i] == '-')
		sasm->i++;
	if (row[sasm->i] == ':' || ft_strchr(LABEL_CHARS, row[sasm->i]))
	{
		type = row[sasm->i] == ':' ? DIRECT_LABEL : DIRECT;
		row[sasm->i] == ':' ? sasm->i++ : sasm->i;
		row[sasm->start] == ':' ? sasm->start++ : sasm->start;
		while (row[sasm->i] && ft_strchr(LABEL_CHARS, row[sasm->i]))
			sasm->i++;
		if ((sasm->i - sasm->start) && is_delimiter(row[sasm->i]))
			parse_chars_type(sasm, row, type);
	}
	else
		error_f("lexico", 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 18:28:08 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 16:51:56 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse_command(t_asm *sasm, char *row)
{
	int		start;
	t_token	*token;

	token = init_token(sasm, COMMAND);
	start = ++(sasm->i);
	while (row[sasm->i] && ft_strchr(LABEL_CHARS, row[sasm->i]))
		sasm->i++;
	if ((sasm->i - start) &&
	(is_whitespace(row[sasm->i]) || row[sasm->i] == '"'))
	{
		token->content = ft_strsub(row, start, sasm->i - start);
		if (token->content == NULL)
			error_f("ft_strsub malloc", 0);
		add_token(sasm, token);
	}
	else
	{
		if (token)
			free(token);
		error_f("Lexical error at", 2);
	}
}

void	fill_token_content(const t_asm *sasm, const char *row,
						int start, t_token *token)
{
	char	*temp;

	temp = ft_strsub(row, start, sasm->i - start);
	if (!temp)
		error_f("ft_strsub malloc", 0);
	if (token->content)
	{
		if (!((token->content = ft_strjoin_free(token->content, temp, 0))))
			error_f("ft_strjoin malloc", 0);
	}
	else
		token->content = temp;
}

void	parse_string(t_asm *sasm, char *row)
{
	int		start;
	t_token	*token;

	start = ++(sasm->i);
	token = init_token(sasm, STRING);
	while (row[sasm->i] != '"')
	{
		if (!(row[sasm->i]))
		{
			fill_token_content(sasm, row, start, token);
			row = sasm->file[++(sasm->row)];
			sasm->i = 0;
			start = sasm->i;
		}
		else
			sasm->i++;
	}
	fill_token_content(sasm, row, start, token);
	add_token(sasm, token);
	sasm->i++;
}

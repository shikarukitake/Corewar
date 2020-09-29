/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:22:50 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 16:29:31 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_ctype			token_type(t_list *tokens)
{
	return (((t_token*)(tokens->content))->type);
}

unsigned char	arg_type(t_list *tokens)
{
	if (token_type(tokens) == DIRECT ||
		token_type(tokens) == DIRECT_LABEL)
		return (T_DIR);
	else if (token_type(tokens) == INDIRECT ||
			token_type(tokens) == INDIRECT_LABEL)
		return (T_IND);
	else if (token_type(tokens) == REGISTER)
		return (T_REG);
	else
		return (T_LAB);
}

unsigned char	arg_type_code(t_list *tokens)
{
	if (token_type(tokens) == DIRECT ||
		token_type(tokens) == DIRECT_LABEL)
		return (C_DIR);
	else if (token_type(tokens) == INDIRECT ||
			token_type(tokens) == INDIRECT_LABEL)
		return (C_IND);
	else if (token_type(tokens) == REGISTER)
		return (C_REG);
	else
		return (0);
}

t_list			*select_next_token(t_list *tokens, const t_op *op, int i)
{
	if (i + 1 != op->count_arg)
	{
		if (token_type(tokens->next) != SEPARATOR)
			error_token("There is no separator", tokens->next->content);
		tokens = tokens->next->next;
	}
	else
		tokens = tokens->next;
	return (tokens);
}

unsigned char	get_type_code(t_list *tokens, t_op *op, int i)
{
	unsigned char	code;
	int				shift;

	code = 0;
	shift = 6;
	while (i != op->count_arg)
	{
		if ((arg_type(tokens) & op->type[i]) == 0)
			error_token("Wrong arguments for token", tokens->content);
		code |= (arg_type_code(tokens) << shift);
		shift -= 2;
		tokens = select_next_token(tokens, op, i);
		i++;
	}
	if (token_type(tokens) != NEW_LINE)
		error_token("No new line after arguments", tokens->content);
	return (code);
}

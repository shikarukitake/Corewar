/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 12:36:18 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 16:50:51 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_list			*procces_operator(t_asm *sasm, t_list *tokens)
{
	t_op	op;
	int		i;

	op = get_op(tokens);
	if (op.name == 0)
		error_token("wrong OPERATOR", tokens->content);
	sasm->curr_start = sasm->i;
	sasm->code[sasm->i++] = op.op_cod;
	tokens = tokens->next;
	if (op.have_arg_code)
		sasm->code[sasm->i++] = get_type_code(tokens, &op, 0);
	i = 0;
	while (i != op.count_arg)
	{
		if ((arg_type(tokens) & op.type[i]) == 0)
			error_token("Wrong arguments for token", tokens->content);
		process_args(sasm, tokens, op.dir_size);
		tokens = select_next_token(tokens, &op, i);
		i++;
	}
	return (tokens->next);
}

t_list			*process_labels(t_asm *sasm, t_list *tokens)
{
	t_token	*token;
	t_label	*label;

	token = tokens->content;
	label = new_label(token->content, sasm->i);
	if (!ft_lst_pb(&(sasm->labels), label, sizeof(t_label)))
		error_f("procces_labels ft_lst_pb", 0);
	return (tokens->next);
}

void			check_code_size(t_asm *sasm)
{
	if ((sasm->i + 14) >= sasm->code_size)
	{
		sasm->code_size *= 2;
		sasm->code = realloc((void*)sasm->code,
		sizeof(char) * (sasm->code_size + 1));
		if (!sasm->code)
			error_f("convert_tokens realloc error", 0);
		sasm->code[sasm->code_size] = 0;
	}
}

void			convert_tokens(t_asm *sasm, t_list *tokens)
{
	sasm->i = 0;
	sasm->code = malloc(sizeof(char) * (CHAMP_MAX_SIZE + 1));
	if (!sasm->code)
		error_f("convert_tokens malloc error", 0);
	sasm->code[CHAMP_MAX_SIZE] = 0;
	sasm->code_size = CHAMP_MAX_SIZE;
	tokens = skip_name_and_comment(tokens);
	while (tokens->next)
	{
		check_code_size(sasm);
		if (token_type(tokens) == NEW_LINE)
			tokens = tokens->next;
		else if (token_type(tokens) == OPERATOR)
			tokens = procces_operator(sasm, tokens);
		else if (token_type(tokens) == LABEL)
			tokens = process_labels(sasm, tokens);
		else
			error_token("Unknown token", tokens->content);
	}
	sasm->code[sasm->i] = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 12:36:18 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/20 14:19:47 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_list	*skip_name_and_comment(t_list *tokens)
{
	while (((t_token*)(tokens->content))->type == NEW_LINE)
		tokens = tokens->next;
	if (((t_token*)(tokens->content))->type != COMMAND)
		error_f("First COMMAND token", 0);
	tokens = tokens->next->next;
	if (((t_token*)(tokens->content))->type != NEW_LINE)
		error_f("No new_line after command", 0);
	while (((t_token*)(tokens->content))->type == NEW_LINE)
		tokens = tokens->next;
	if (((t_token*)(tokens->content))->type != COMMAND)
		error_f("First COMMAND token", 0);
	tokens = tokens->next->next;
	if (((t_token*)(tokens->content))->type != NEW_LINE)
		error_f("No new_line after command", 0);
	return (tokens->next);
}

t_ctype	token_type(t_list *tokens)
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

t_op		get_op(t_list *tokens)
{
	int		len;
	int		i;
	t_token	*token;

	token = tokens->content;
	len = 16;
	i = 0;
	while (i != len)
	{
		if (!ft_strcmp(token->content, op_tab[i].name))
			return (op_tab[i]);
		i++;
	}
	return (op_tab[16]);
}

t_list *select_next_token(t_list *tokens, const t_op *op, int i)
{
	if (i + 1 != op->count_arg)
	{
		if (token_type(tokens->next) != SEPARATOR)
			error_f("There is no separator", 0);//todo where is separator
		tokens = tokens->next->next;
	}
	else
		tokens = tokens->next;
	return tokens;
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
			error_f("Wrong arguments for token", 0);//todo name of token in error
		code |= (arg_type_code(tokens) << shift);
		shift -= 2;
		tokens = select_next_token(tokens, op, i);
		i++;
	}
	if (token_type(tokens) != NEW_LINE)
		error_f("No new line after arguments", 0);//todo where is
	return (code);
}


void	procces_register(t_asm *sasm, t_token *token)
{
	sasm->code[sasm->i++] = ft_atoi(token->content + 1);
}

t_ref_label	*new_ref(char *name, int start, int end, int comm_start, t_ctype type)
{
	t_ref_label		*ref;

	ref = malloc(sizeof(t_ref_label));
	if (ref == NULL)
		error_f("new_ref malloc", 0);
	ref->name = ft_strdup(name);
	if (ref->name == NULL)
		error_f("new_ref malloc", 0);
	ref->comm_start = comm_start;
	ref->type = type;
	ref->start = start;
	ref->end = end;
	return (ref);
}

void	procces_dir(t_asm *sasm, t_token *token, int dir_size)
{
	unsigned int	code;

	if (token->type == DIRECT_LABEL)
	{
		if (!ft_lst_pb(&(sasm->ref_labels), new_ref(token->content, sasm->i,
		sasm->i + dir_size, sasm->curr_start, token->type), sizeof(t_ref_label)))
			error_f("proccess_dir lst malloc", 0);
		code = 0;
		while (dir_size != 0)
		{
			sasm->code[sasm->i++] = code >> (8 * (dir_size - 1));
			dir_size--;
		}
	}
	else if (token->type == DIRECT)
	{
		code = ft_atoi32(token->content);//todo check
		while (dir_size != 0)
		{
			sasm->code[sasm->i++] = code >> (8 * (dir_size - 1));
			dir_size--;
		}
	}
}

void	procces_ind(t_asm *sasm, t_token *token)
{
	unsigned int	code;

	if (token->type == INDIRECT_LABEL)
	{
		if (!ft_lst_pb(&(sasm->ref_labels), new_ref(token->content, sasm->curr_start,
		sasm->i + 2, sasm->i, token->type), sizeof(t_ref_label)))
			error_f("proccess_dir lst malloc", 0);
		code = 0;
		sasm->code[sasm->i++] = code >> 8;
		sasm->code[sasm->i++] = code;
	}
	else
	{
		code = ft_atoi32(token->content);//todo check
		sasm->code[sasm->i++] = code >> 8;
		sasm->code[sasm->i++] = code;
	}
}


void	process_args(t_asm *sasm, t_list *tokens, int dir_size)
{
	if (arg_type(tokens) == T_REG)
		procces_register(sasm, tokens->content);
	else if (arg_type(tokens) == T_DIR)
		procces_dir(sasm, tokens->content, dir_size);
	else if (arg_type(tokens) == T_IND)
		procces_ind(sasm, tokens->content);
	else
		error_f("Something wrong", 0);
}

t_list		*procces_operator(t_asm *sasm, t_list *tokens)
{
	t_op	op;
	int		i;

	op = get_op(tokens);
	if (op.name == 0)
		error_f("wrong OPERATOR", 0);//todo print token content and row and i
	sasm->curr_start = sasm->i;
	sasm->code[sasm->i++] = op.op_cod;
	tokens = tokens->next;
	if (op.have_arg_code)
		sasm->code[sasm->i++] = get_type_code(tokens, &op, 0);
	i = 0;
	while (i != op.count_arg)
	{
		if ((arg_type(tokens) & op.type[i]) == 0)
			error_f("Wrong arguments for token", 0);//todo name of token in error
		process_args(sasm, tokens, op.dir_size);
		tokens = select_next_token(tokens, &op, i);
		i++;
	}
	return (tokens->next);
}

void	check_code_size(t_asm *sasm)
{
	if ((sasm->i + 14) >= sasm->code_size)
	{
		sasm->code_size *= 2;
		sasm->code = realloc((void*)sasm->code, sizeof(char) * (sasm->code_size + 1));
		if (!sasm->code)
			error_f("convert_tokens realloc error", 0);
		sasm->code[sasm->code_size] = 0;
	}
}

t_label	*new_label(char *name, int point)
{
	t_label	*label;

	label = malloc(sizeof(t_label));
	if (label == NULL)
		error_f("new_label malloc", 0);
	label->name = ft_strdup(name);
	if (label->name == NULL)
		error_f("new_label malloc", 0);
	label->point = point;
	return (label);
}

t_list	*process_labels(t_asm *sasm, t_list *tokens)
{
	t_token	*token;
	t_label	*label;

	token = tokens->content;
	label = new_label(token->content, sasm->i);
	if (!ft_lst_pb(&(sasm->labels), label, sizeof(t_label)))
		error_f("procces_labels ft_lst_pb", 0);
	return (tokens->next);
}

void	convert_tokens(t_asm *sasm, t_list *tokens)
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
			error_f("Unknown token", 0);//todo row index in error
	}
	sasm->code[sasm->i] = 0;
}
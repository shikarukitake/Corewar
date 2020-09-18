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
		if (i + 1 != op->count_arg)
		{
			if (token_type(tokens->next) != SEPARATOR)
				error_f("There is no separator", 0);//todo where is separator
			tokens = tokens->next->next;
		}
		else
			tokens = tokens->next;
		i++;
	}
	if (token_type(tokens) != NEW_LINE)
		error_f("No new line after arguments", 0);//todo where is
	return (code);
}

t_list		*procces_operator(t_asm *sasm, t_list *tokens)
{
	t_op	op;
	int		i;

	op = get_op(tokens);
	if (op.name == 0)
		error_f("wrong OPERATOR", 0);//todo print token content and row and i
	sasm->code[sasm->i++] = op.op_cod;
	tokens = tokens->next;
	if (op.have_arg_code)
		sasm->code[sasm->i++] = get_type_code(tokens, &op, 0);
	i = 0;
	while (i != op.count_arg)
	{

		i++;
	}
	return (tokens->next);
}

void check_code_size(t_asm *sasm)
{
	if ((sasm->i + 14) >= CHAMP_MAX_SIZE)
	{
		sasm->code_size *= 2;
		sasm->code = realloc((void*)sasm->code, sizeof(char) * (sasm->code_size + 1));
		if (!sasm->code)
			error_f("convert_tokens realloc error", 0);
		sasm->code[sasm->code_size] = 0;
	}
}

t_list *process_labels(t_asm *sasm, t_list *tokens)
{
	return (tokens->next);
}

void	print_hex(t_asm *sasm)
{
	int	i = 0;

	while (i != sasm->code_size)
	{
		ft_printf("%x ", sasm->code[i]);
		i++;
	}
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
		if (sasm->i > 600)
		{
			print_hex(sasm);
			free_asm(sasm);
			exit(0);
		}
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
}
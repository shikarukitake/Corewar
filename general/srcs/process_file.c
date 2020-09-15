#include "asm.h"

void	print_file(t_asm *sasm)//todo service function delete
{
	int	i = 0;
	while (sasm->file[i])
	{
		ft_printf("%s", sasm->file[i]);
		i++;
	}
}


void	parse_chars_type(t_asm *sasm, char *row, t_ctype type)
{
	t_token	*token;

	token = init_token(sasm, type);
	token->content = ft_strsub(row, sasm->start, sasm->i - sasm->start);
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
			parse_chars_type(sasm, row, OPERATOR);//todo some check
	}
	else
		error_f("lexico", 2);
}


void	parse_direct(t_asm *sasm, char *row)
{
	t_ctype	type;

	sasm->start = ++sasm->i;
	if (row[sasm->i] == ':' || ft_strchr(LABEL_CHARS, row[sasm->i]))
	{
		type = row[sasm->i] == ':' ? DIRECT_LABEL : DIRECT;
		row[sasm->i] == ':' ? sasm->i++ : sasm->i;
		sasm->start = row[sasm->start] == ':' ? sasm->start++ : sasm->start;
		while (row[sasm->i] && ft_strchr(LABEL_CHARS, row[sasm->i]))
			sasm->i++;
		if ((sasm->i - sasm->start) && is_delimiter(row[sasm->i]))
			parse_chars_type(sasm, row, type);
	}
	else
		error_f("lexico", 2);
}

void	parse_indirect(t_asm *sasm, char *row)
{
	sasm->start = ++sasm->i;
	while (row[sasm->i] && ft_strchr(LABEL_CHARS, row[sasm->i]))
		sasm->i++;
	if ((sasm->i - sasm->start) && is_delimiter(row[sasm->i]))
		parse_chars_type(sasm, row, INDIRECT_LABEL);
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
	else
		error_f("undefined ch when parsing", 2);
}

void	parse_tokens(t_asm *sasm)
{
	sasm->row = 0;

	while (sasm->file[sasm->row])
	{
		sasm->i = 0;
		while (sasm->file[sasm->row] && sasm->file[sasm->row][sasm->i])
		{
			skip_whitespace(sasm, sasm->file[sasm->row]);
			skip_comment(sasm, sasm->file[sasm->row]);
			if (sasm->file[sasm->row][sasm->i])
				parse_token(sasm, sasm->file[sasm->row]);
		}
		if (!(sasm->file[sasm->row]))
			break;
		sasm->row++;
	}
}

void	process_file(t_asm *sasm)
{
	print_file(sasm);
	parse_tokens(sasm);
	ft_lstiter_n(sasm->tokens, &print_token);
}
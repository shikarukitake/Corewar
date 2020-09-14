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

void	parse_token(t_asm *sasm, char *row)
{
	if (row[sasm->i] == COMMAND_CHAR)
		parse_command(sasm, row);
	else if (row[sasm->i] == '\n')
	{
		add_token(sasm, init_token(sasm, NEW_LINE));
		sasm->row++;
	}
	else
	{

	}
}

void	parse_tokens(t_asm *sasm)
{
	sasm->row = 0;
	sasm->i = 0;
	while (sasm->file[sasm->row])
	{
		while (sasm->file[sasm->row][sasm->i])
		{
			skip_whitespace(sasm, sasm->file[sasm->row]);
			skip_comment(sasm, sasm->file[sasm->row]);
			if (sasm->file[sasm->row][sasm->i])
				parse_token(sasm, sasm->file[sasm->row]);
		}
		sasm->row++;
	}
}

void	process_file(t_asm *sasm)
{
	print_file(sasm);
	parse_tokens(sasm);
}
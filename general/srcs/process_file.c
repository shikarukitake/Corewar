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


void	check_end(t_asm *sasm)
{
	t_list	*tokens;

	tokens = sasm->tokens;
	while (tokens->next)
		tokens = tokens->next;
	if (((t_token*)(tokens->content))->type != NEW_LINE)
		error_f("No new_line at the end of file", 0);
}

void	process_file(t_asm *sasm)
{
	print_file(sasm);
	parse_tokens(sasm);
	check_end(sasm);
	add_token(sasm, init_token(sasm, END));
	ft_lstiter_n(sasm->tokens, &print_token);
	ft_lstiter_ext_n(sasm->tokens, sasm, &find_name_and_comment);
	if ((!sasm->prog_name[0] || !sasm->comment[0]))
		error_f("There is no name or comment", 0);

	convert_tokens(sasm, sasm->tokens);

}
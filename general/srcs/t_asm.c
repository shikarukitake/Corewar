#include "asm.h"

t_asm	*init_asm(void)
{
	t_asm	*sasm;

	sasm = malloc(sizeof(t_asm));
	if (!sasm)
		ft_error_t("init_asm malloc");
	else
	{
		sasm->magic = 0;
		sasm->prog_size = 0;
		sasm->code = NULL;
		sasm->tokens = NULL;
		sasm->fd = 0;
		sasm->i = -1;
		sasm->row = -1;
		sasm->line = NULL;
		sasm->dline = NULL;
		sasm->prog_name[0] = 0;
		sasm->comment[0] = 0;
	}
	return (sasm);
}

void	del_tokens(void *content, size_t size)
{
	t_token	*token;

	token = content;
	if (token)
	{
		if (token->content)
			free(token->content);
		free(token);
	}
}

void	free_asm(t_asm *sasm)
{
	if (sasm)
	{
		if (sasm->code)
			free(sasm->code);
		if (sasm->tokens)
			ft_lstdel(&(sasm->tokens), &del_tokens);
		if (sasm->line)
			free(sasm->line);
		if (sasm->dline)
			to_free_dstr(sasm->dline);
		if (sasm->file)
			to_free_dstr(sasm->file);
		free(sasm);
	}
}
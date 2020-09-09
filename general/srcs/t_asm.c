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
		sasm->i = 0;
		sasm->row = 0;
	}
	return (sasm);
}

void	del_tokens(void *list, size_t size)
{
	//todo create
}

void	free_asm(t_asm *sasm)
{
	if (sasm->code)
		free(sasm->code);
	if (sasm->tokens)
		ft_lstdel(&(sasm->tokens), &del_tokens);
	free(sasm);
}
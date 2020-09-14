#include "asm.h"

void	print_token(t_list *list)
{
	t_token		*token;

	token = list->content;
	ft_printf("\nContent:'%s'\nType:%d\n", token->content, token->type);
}
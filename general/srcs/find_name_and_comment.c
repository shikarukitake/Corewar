#include "asm.h"


void get_content(t_token *token, int name_or_comment, char *name)
{
	int		i;
	int		len;

	len = name_or_comment == 0 ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	i = 0;
	if (token->type == STRING)
	{
		while (token->content[i])
		{
			if (i > len)
				error_f("Wrong lenght of name or comment", 0);
			name[i] = token->content[i];
			i++;
		}
	}
	else
		error_f("There is no string token after name or comment", 0);
}

void	find_name_and_comment(t_list *list, void *stuff)
{
	t_asm	*sasm;
	t_token	*token;

	sasm = stuff;
	token = list->content;
	if (token->type == COMMAND)
	{
		if (!ft_strcmp(token->content, "name") && !sasm->prog_name[0])
		{
			if (list->next)
				get_content(list->next->content, 0, sasm->prog_name);
			else
				error_f("There is no content for name token", 0);//todo row and i complete
		}
		else if (!ft_strcmp(token->content, "comment") && !sasm->comment[0])
		{
			if (list->next)
				get_content(list->next->content,1, sasm->comment);
			else
				error_f("There is no content for comment token", 0);//todo row and i complete
		}
		else
			error_f("Unknown command token", 0);//todo row and i complete
	}
}
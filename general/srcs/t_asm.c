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
		sasm->labels = NULL;
		sasm->ref_labels = NULL;
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

void	del_ref_labels(void *content, size_t size)
{
	t_ref_label	*ref_label;

	size += 0;
	ref_label = content;
	if (ref_label)
	{
		if (ref_label->name)
			free(ref_label->name);
		free(ref_label);
	}
}

void	del_labels(void *content, size_t size)
{
	t_label	*label;

	size += 0;
	label = content;
	if (label)
	{
		if (label->name)
			free(label->name);
		free(label);
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
		if (sasm->ref_labels)
			ft_lstdel(&(sasm->ref_labels), &del_ref_labels);
		if (sasm->labels)
			ft_lstdel(&(sasm->labels), &del_labels);
		free(sasm);
	}
}
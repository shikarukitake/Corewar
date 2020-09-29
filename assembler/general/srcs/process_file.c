/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 12:37:12 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 16:49:43 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
			break ;
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

int		find_label(void *content, void *find_content)
{
	t_label	*first;
	char	*second;

	first = content;
	second = find_content;
	if (!ft_strcmp(first->name, second))
		return (1);
	else
		return (0);
}

void	convert_labels(t_list *list, void *sas)
{
	t_asm		*sasm;
	t_ref_label	*ref_label;
	unsigned	code;
	t_label		*label;
	t_list		*finded;

	ref_label = list->content;
	sasm = sas;
	finded = ft_lstfind(sasm->labels, &find_label, ref_label->name);
	if (!finded)
		error_token("Can't find reference to token", 0);
	label = finded->content;
	code = label->point - ref_label->comm_start;
	while (ref_label->start != ref_label->end)
	{
		sasm->code[ref_label->start] = code >>
		(8 * (ref_label->end - 1 - ref_label->start));
		ref_label->start++;
	}
}

void	process_file(t_asm *sasm)
{
	parse_tokens(sasm);
	check_end(sasm);
	add_token(sasm, init_token(sasm, END));
	ft_lstiter_ext_n(sasm->tokens, sasm, &find_name_and_comment);
	if ((!sasm->prog_name_e || !sasm->comment_e))
		error_f("There is no name or comment", 0);
	convert_tokens(sasm, sasm->tokens);
	if (sasm->i == 0)
		error_f("There is no code", 0);
	ft_lstiter_ext(sasm->ref_labels, sasm, &convert_labels);
}

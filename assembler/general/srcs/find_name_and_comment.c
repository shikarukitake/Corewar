/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_name_and_comment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 12:36:46 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/20 13:02:06 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	get_content(t_token *token, int name_or_comment, char *name)
{
	int		i;
	size_t	len;

	len = name_or_comment == 0 ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	if (ft_strlen(token->content) > len)
		error_f("Wrong lenght of name or comment", 0);
	i = 0;
	if (token->type == STRING)
	{
		while (token->content[i])
		{
			if ((size_t)i > len)
				error_f("Wrong lenght of name or comment", 0);
			name[i] = token->content[i];
			i++;
		}
		return (1);
	}
	else
		error_f("There is no string token after name or comment", 0);
	return (0);
}

void	find_name_and_comment(t_list *list, void *stuff)
{
	t_asm	*sasm;
	t_token	*token;

	sasm = stuff;
	token = list->content;
	if (token->type == COMMAND)
	{
		if (!ft_strcmp(token->content, "name") && !sasm->prog_name_e)
		{
			if (list->next)
				sasm->prog_name_e = get_content(list->next->content, 0, sasm->prog_name);
			else
				error_f("There is no content for name token", 0);//todo row and i complete
		}
		else if (!ft_strcmp(token->content, "comment") && !sasm->comment_e)
		{
			if (list->next)
				sasm->comment_e = get_content(list->next->content, 1, sasm->comment);
			else
				error_f("There is no content for comment token", 0);//todo row and i complete
		}
		else
			error_f("Unknown command token", 0);//todo row and i complete
	}
}
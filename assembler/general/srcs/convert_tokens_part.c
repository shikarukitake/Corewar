/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tokens_part.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:34:40 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 16:35:35 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_list			*skip_name_and_comment(t_list *tokens)
{
	while (((t_token*)(tokens->content))->type == NEW_LINE)
		tokens = tokens->next;
	if (((t_token*)(tokens->content))->type != COMMAND)
		error_f("First COMMAND token", 0);
	tokens = tokens->next->next;
	if (((t_token*)(tokens->content))->type != NEW_LINE)
		error_f("No new_line after command", 0);
	while (((t_token*)(tokens->content))->type == NEW_LINE)
		tokens = tokens->next;
	if (((t_token*)(tokens->content))->type != COMMAND)
		error_f("First COMMAND token", 0);
	tokens = tokens->next->next;
	if (((t_token*)(tokens->content))->type != NEW_LINE)
		error_f("No new_line after command", 0);
	return (tokens->next);
}

t_op			get_op(t_list *tokens)
{
	int		len;
	int		i;
	t_token	*token;

	token = tokens->content;
	len = 16;
	i = 0;
	while (i != len)
	{
		if (!ft_strcmp(token->content, g_op_tab[i].name))
			return (g_op_tab[i]);
		i++;
	}
	return (g_op_tab[16]);
}

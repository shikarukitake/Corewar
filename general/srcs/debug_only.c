/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_only.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 12:36:34 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/20 12:36:34 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*strctypes[] =
		{
				"OPERATOR",
				"COMMAND",
				"STRING",
				"REGISTER",
				"SEPARATOR",
				"LABEL",
				"DIRECT",
				"DIRECT_LABEL",
				"INDIRECT",
				"INDIRECT_LABEL",
				"NEW_LINE",
				"END"
		};

void	print_token(t_list *list)
{
	t_token		*token;

	token = list->content;
	ft_printf("\nContent:'%s'\nType:%s\n", token->content, strctypes[token->type]);
}
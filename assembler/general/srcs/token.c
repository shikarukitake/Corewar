/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 18:18:06 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 14:35:21 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token		*init_token(t_asm *sasm, t_ctype type)
{
	t_token		*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		error_f("init_token malloc error", 0);
	token->row = sasm->row;
	token->i = sasm->i;
	token->type = type;
	token->content = NULL;
	return (token);
}

void		add_token(t_asm *sasm, t_token	*token)
{
	if (!ft_lst_pb(&(sasm->tokens), token, sizeof(t_token)))
		error_f("ft_lst_pb malloc", 0);
}
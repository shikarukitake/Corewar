/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:01:23 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/15 19:26:37 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse_label(t_asm *sasm, char *row)//todo Remove skipping chars
{
	t_token	*token;

	token = init_token(sasm, LABEL);
	sasm->i++;
	token->content = ft_strsub(row, sasm->start, sasm->i - sasm->start);
	if (token->content == NULL)
		error_f("ft_strsub malloc", 0);
	add_token(sasm, token);
}
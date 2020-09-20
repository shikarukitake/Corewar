/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_small.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:43:43 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/15 20:43:43 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse_newline(t_asm *sasm)
{
	add_token(sasm, init_token(sasm, NEW_LINE));
	sasm->row++;
	sasm->i = 0;
}

void	parse_separator(t_asm *sasm)
{
	add_token(sasm, init_token(sasm, SEPARATOR));
	sasm->i++;
}

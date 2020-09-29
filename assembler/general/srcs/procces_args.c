/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procces_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:40:53 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 16:42:13 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	procces_register(t_asm *sasm, t_token *token)
{
	sasm->code[sasm->i++] = ft_atoi(token->content + 1);
}

void	process_dir_label(t_asm *sasm, const t_token *token, int dir_size)
{
	unsigned int	code;
	unsigned int	start_end[2];

	start_end[0] = sasm->i;
	start_end[1] = sasm->i + dir_size;
	if (!ft_lst_pb(&(sasm->ref_labels), new_ref(token->content, start_end,
			sasm->curr_start, token->type), sizeof(t_ref_label)))
		error_f("proccess_dir lst malloc", 0);
	code = 0;
	while (dir_size != 0)
	{
		sasm->code[sasm->i++] = code >> (8 * (dir_size - 1));
		dir_size--;
	}
}

void	procces_dir(t_asm *sasm, t_token *token, int dir_size)
{
	unsigned int	code;

	if (token->type == DIRECT_LABEL)
		process_dir_label(sasm, token, dir_size);
	else if (token->type == DIRECT)
	{
		code = ft_atoi32(token->content);
		while (dir_size != 0)
		{
			sasm->code[sasm->i++] = code >> (8 * (dir_size - 1));
			dir_size--;
		}
	}
}

void	procces_ind(t_asm *sasm, t_token *token)
{
	unsigned int	code;
	unsigned int	start_end[2];

	if (token->type == INDIRECT_LABEL)
	{
		start_end[0] = sasm->i;
		start_end[1] = sasm->i + 2;
		if (!ft_lst_pb(&(sasm->ref_labels), new_ref(token->content, start_end,
						sasm->curr_start, token->type), sizeof(t_ref_label)))
			error_f("proccess_dir lst malloc", 0);
		code = 0;
		sasm->code[sasm->i++] = code >> 8;
		sasm->code[sasm->i++] = code;
	}
	else
	{
		code = ft_atoi32(token->content);
		sasm->code[sasm->i++] = code >> 8;
		sasm->code[sasm->i++] = code;
	}
}

void	process_args(t_asm *sasm, t_list *tokens, int dir_size)
{
	if (arg_type(tokens) == T_REG)
		procces_register(sasm, tokens->content);
	else if (arg_type(tokens) == T_DIR)
		procces_dir(sasm, tokens->content, dir_size);
	else if (arg_type(tokens) == T_IND)
		procces_ind(sasm, tokens->content);
	else
		error_f("Something wrong", 0);
}

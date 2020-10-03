/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 23:03:11 by sdagger           #+#    #+#             */
/*   Updated: 2020/10/03 23:03:12 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_bool		is_champ(const char *filename, const char *ext)
{
	if (filename && ext && ft_strlen(filename) >= ft_strlen(ext))
		return (!ft_strcmp(ft_strchr(filename, '\0') - ft_strlen(ext), ext));
	else
		return (FALSE);
}

void		set_arg_type(char arg_type, char index, t_cursor *cursor)
{
	cursor->args_types[index - 1] = g_arg_code[arg_type - 1];
}

void		parse_types_code(t_vm *vm, t_cursor *cursor, t_op *op)
{
	char args_types_code;

	if (op->args_types_code)
	{
		args_types_code = get_byte(vm, cursor->pc, 1);
		if (op->args_num >= 1)
			set_arg_type((char)((args_types_code & 0xC0) >> 6), 1, cursor);
		if (op->args_num >= 2)
			set_arg_type((char)((args_types_code & 0x30) >> 4), 2, cursor);
		if (op->args_num >= 3)
			set_arg_type((char)((args_types_code & 0xC) >> 2), 3, cursor);
	}
	else
		cursor->args_types[0] = op->args_types[0];
}

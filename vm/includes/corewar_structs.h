/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 16:45:46 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/09/29 11:22:59 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H 
# define COREWAR_H


# include "libft.h"
# include "corewar_errors.h"
# include "op.h"
# include <stdio.h>
# include <stdlib.h>


typedef enum {
    FALSE,
    TRUE
} t_bool;

typedef struct	s_op
{
	char		*name;
	unsigned char		code;
	unsigned char		args_num;
	t_bool		args_types_code;
	unsigned char		args_types[3];
	t_bool		modify_carry;
	unsigned char		t_dir_size;
	unsigned int	cycles;
	void		(*func)(t_vm *, t_cursor *);

}				t_op;

typedef struct			s_player
{
	int				id;
	char				*name;
	char				*comment;
	int				code_size;
	unsigned char				*code;
	size_t				current_lives_num;
	size_t				previous_lives_num;
	ssize_t				last_live;
	struct s_player		*next;
}						t_player;

typedef struct			s_cursor
{
	unsigned int			id;
	t_bool				carry;
	unsigned char				op_code;
	ssize_t				last_live;
	int					cycles_to_exec;
	unsigned char				args_types[3];
	int				pc;
	unsigned int			step;
	int				reg[REG_NUMBER];
	t_player			*player;
	struct s_cursor		*next;
}						t_cursor;

typedef struct			s_vm
{
	unsigned char				arena[MEM_SIZE];
	t_player			*players[MAX_PLAYERS];
	int				players_num;
	t_player			*last_alive;
	t_cursor			*cursors;
	size_t				cursors_num;
	size_t				lives_num;
	ssize_t				cycles;
	ssize_t				cycles_to_die;
	ssize_t				cycles_after_check;
	size_t				checks_num;
	struct s_vs			*vs;
	ssize_t				dump_cycle;
	int					dump_print_mode;
	ssize_t				show_cycle;
	int					show_print_mode;
	t_bool				display_aff;
	int					log;
}						t_vm;


#endif
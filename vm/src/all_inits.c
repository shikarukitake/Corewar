/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_inits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 18:59:12 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/10/03 17:00:34 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_structs.h"

t_player	*init_player(int id)
{
	t_player *player;

	if (!(player = (t_player *)ft_memalloc(sizeof(t_player))))
		
	player->id = id;
	player->name = NULL;
	player->comment = NULL;
	player->code_size = 0;
	player->code = NULL;
	player->last_live = 0;
	player->current_lives_num = 0;
	player->previous_lives_num = 0;
	player->next = NULL;
	return (player);
}

t_cursor	*init_cursor(t_player *player, int pc)
{
	t_cursor		*cursor;
	static unsigned int cursor_id;

	if (!(cursor = (t_cursor *)ft_memalloc(sizeof(t_cursor))))
	cursor->id = ++cursor_id;
	cursor->carry = FALSE;
	cursor->op_code = 0;
	cursor->last_live = 0;
	cursor->cycles_to_exec = 0;
	cursor->pc = pc;
	cursor->next = NULL;
	cursor->reg[INDEX(1)] = -(player->id);
	cursor->player = player;
	return (cursor);
}

t_vm		*init_vm(void)
{
	t_vm *vi_ma;

	if (!(vi_ma = (t_vm *)ft_memalloc(sizeof(t_vm))))
	vi_ma->players_num = 0;
	vi_ma->last_alive = NULL;
	vi_ma->cursors = NULL;
	vi_ma->cursors_num = 0;
	vi_ma->lives_num = 0;
	vi_ma->cycles = 0;
	vi_ma->cycles_to_die = CYCLE_TO_DIE;
	vi_ma->cycles_after_check = 0;
	vi_ma->checks_num = 0;
	vi_ma->dump_cycle = -1;
	vi_ma->dump_print_mode = 0;
	vi_ma->show_cycle = -1;
	vi_ma->show_print_mode = 0;
	vi_ma->display_aff = FALSE;
	vi_ma->log = 0;
	return (vi_ma);
}

void		init_arena(t_vm *vi_ma)
{
	int			id;
	unsigned int	pc;

	id = 1;
	pc = 0;
	while (id <= vi_ma->players_num)
	{
		ft_memcpy(&(vi_ma->arena[pc]),
			vi_ma->players[INDEX(id)]->code,
			(size_t)(vi_ma->players[INDEX(id)]->code_size));
		pc += MEM_SIZE / vi_ma->players_num;
		id++;
	}
}
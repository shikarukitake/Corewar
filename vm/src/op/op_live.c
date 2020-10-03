/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 20:23:16 by ablizniu          #+#    #+#             */
/*   Updated: 2020/10/03 16:20:35 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_structs.h"

inline static void	log_live(unsigned int cursor_id, int player_id)
{
	ft_printf("P %4d | live %d\n", cursor_id, player_id);
}

inline static void	log_live_msg(int player_id, char *player_name)
{
	ft_printf("Player %d (%s) is said to be alive\n",
													player_id,
													player_name);
}

void				op_live(t_vm *vm, t_cursor *cursor)
{
	int		player_id;
	t_player	*player;

	cursor->step += OP_CODE_LEN;
	player_id = get_op_arg(vm, cursor, 1, FALSE);
	vm->lives_num++;
	cursor->last_live = vm->cycles;
	player = NULL;
	if (player_id <= -1 && player_id >= -((int)vm->players_num))
	{
		player = vm->players[INDEX(FT_ABS(player_id))];
		player->last_live = vm->cycles;
		player->current_lives_num++;
		vm->last_alive = player;
	}
	if (vm->log & OP_LOG)
		log_live(cursor->id, player_id);
	if (vm->log & LIVE_LOG && player)
		log_live_msg(FT_ABS(player_id), player->name);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 13:22:44 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/09/20 18:39:50 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_structs.h"


static void	add_player(t_player **player_l, t_player *new)
{
	t_player *current;

	if (player_l && new)
	{
		if (*player_l)
		{
			current = *player_l;
			while (current->next)
				current = current->next;
			current->next = new;
		}
		else
			*player_l = new;
	}
}

static void	parse_champion_filename(int *ac, char ***av, t_vm *vi_ma,
									t_player **player_l)
{
	int32_t id;

	id = 0;
	if (*ac >= 3 && !ft_strcmp(**av, "-n"))
	{
		if (!check_integer(*(*av + 1))
			|| (id = ft_atoi(*(*av + 1))) < 1
			|| id > MAX_PLAYERS
			|| find_player(*player_l, id)
			|| !is_filename(*(*av + 2), ".cor"))
			err_func();
		add_player(player_l, parse_champion(*(*av + 2), id));
		vi_ma->players_num++;
		(*ac) -= 3;
		(*av) += 3;
	}   
	else if (is_filename(**av, ".cor"))
	{
		add_player(player_l, parse_champion(**av, id));
		vi_ma->players_num++;
		(*ac)--;
		(*av)++;
	}
	else
		err_func();
}

static void	update_players(t_player *player_l)
{
	t_player	*player;
	int32_t		id;

	id = 1;
	player = player_l;
	while (player)
	{
		if (player->id == 0)
		{
			while (find_player(player_l, id))
				id++;
			player->id = id;
		}
		player = player->next;
	}
}

static void	set_players(t_vm *vi_ma, t_player *player_l)
{
	int32_t id;

	id = 1;
	update_players(player_l);
	while (id <= vi_ma->players_num)
	{
		if (!(vi_ma->players[id] = find_player(player_l, id)))
			err_func();
		id++;
	}
	vi_ma->last_alive = vi_ma->players[vi_ma->players_num];
}

void		args_parce(int ac, char **av, t_vm *vi_ma)
{
	t_player *player_l;

	player_l = NULL;
	ac--;
	av++;
	while (ac >= 1)
	{
		if (!ft_strcmp(*av, "-v"))
			parse_vs(&ac, &av, vi_ma);
		else if (!ft_strcmp(*av, "-dump") || !ft_strcmp(*av, "-d"))
			parse_dump(&ac, &av, vi_ma);
		else if (!ft_strcmp(*av, "-show") || !ft_strcmp(*av, "-s"))
			parse_show(&ac, &av, vi_ma);
		//else if (!ft_strcmp(*av, "-a"))
		//	parse_aff_flag(&ac, &av, vi_ma);
		else if (!ft_strcmp(*av, "-l"))
			parse_log(&ac, &av, vi_ma);
		else if (!ft_strcmp(*av, "-n") || is_champ(*av, ".cor"))
			parse_champion_filename(&ac, &av, vi_ma, &player_l);
		else
			err_func();
	}
	if (vi_ma->players_num < 1 || vi_ma->players_num > MAX_PLAYERS)
		err_func();
	set_players(vi_ma, player_l);
}
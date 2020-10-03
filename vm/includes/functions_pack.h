/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_pack.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 17:01:55 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/10/03 17:12:34 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_PACK_H
# define FUNCTIONS_PACK_H

# include "corewar_structs.h"

void err_func();

void			op_live(t_vm *vm, t_cursor *pc);
void			op_ld(t_vm *vm, t_cursor *pc);
void			op_st(t_vm *vm, t_cursor *pc);
void			op_add(t_vm *vm, t_cursor *pc);
void			op_sub(t_vm *vm, t_cursor *pc);
void			op_and(t_vm *vm, t_cursor *cursor);
void			op_or(t_vm *vm, t_cursor *cursor);
void			op_xor(t_vm *vm, t_cursor *cursor);
void			op_zjmp(t_vm *vm, t_cursor *cursor);
void			op_ldi(t_vm *vm, t_cursor *cursor);
void			op_sti(t_vm *vm, t_cursor *cursor);
void			op_fork(t_vm *vm, t_cursor *cursor);
void			op_lld(t_vm *vm, t_cursor *cursor);
void			op_lldi(t_vm *vm, t_cursor *cursor);
void			op_lfork(t_vm *vm, t_cursor *cursor);
void			op_aff(t_vm *vm, t_cursor *cursor);

t_player	*init_player(int id);
t_cursor	*init_cursor(t_player *player, int pc);
t_vm		*init_vm(void);
void		init_arena(t_vm *vi_ma);

static void	free_players(t_player **players, int players_num);
static void	free_cursors(t_cursor **list);
void		free_vi_ma(t_vm **vi_ma);

unsigned int	step_size(unsigned char arg_type, t_op *op);
unsigned int	calc_step(t_cursor *cursor, t_op *op);
int		calc_addr(int addr);

void			terminate(char *s);
inline char	get_byte(t_vm *vm, int pc, int step);
t_bool	check_tab(char c);
t_bool	check_integer(const char *str, t_bool strict);
t_player	*find_player(t_player *players_l, int id);

static void		reset_lives_nums(t_vm *vm);
static t_bool	is_died(t_vm *vm, t_cursor *cursor);
static void		delete_died_cursors(t_vm *vm);
void			cycles_to_die_check(t_vm *vm);

inline void	log_cycle(ssize_t cycle);
void		log_pc_movements(unsigned char *arena, t_cursor *cursor);
inline void	log_cursor_death(t_vm *vm, t_cursor *cursor);
inline void	log_cycles_to_die(ssize_t cycles_to_die);

int		bytecode_to_int_utils(const unsigned char *arena, int addr, int size);
static int	parse_int(int fd);
static char		*parse_str(int fd, size_t len);
static unsigned char	*parse_code(int fd, size_t len);
t_player		*parse_champion(char *filename, int id);

void	parse_dump(int *argc, char ***argv, t_vm *vi_ma);
void parce_log(int *ac, char ***av, t_vm *vi_ma);
void	parse_show(int *argc, char ***argv, t_vm *vi_ma);
void	parse_aff(int *argc, char ***argv, t_vm *vi_ma);

void		print_intro(t_player **players, int players_num);
inline void	print_winner(t_vm *vm);
void		print_arena(unsigned char *arena, int print_mode);
void		print_help(void);

static void	add_player(t_player **player_l, t_player *new);
static void	parse_champion_filename(int *ac, char ***av, t_vm *vi_ma,
									t_player **player_l);
static void	update_players(t_player *player_l);
static void	set_players(t_vm *vi_ma, t_player *player_l);
void		args_parce(int ac, char **av, t_vm *vi_ma);

void	update_op_code(t_vm *vm, t_cursor *current);
void	move_cursor(t_vm *vm, t_cursor *cursor);
static void	do_op(t_cursor *cursor, t_vm *vm);
void		in_cycle(t_vm *vm);
void		start(t_vm *vm);

t_bool			is_arg_types_valid(t_cursor *cursor, t_op *op);
static t_bool	is_register(t_vm *vm, int pc, int step);
t_bool			is_args_valid(t_cursor *cursor, t_vm *vm, t_op *op);

#endif
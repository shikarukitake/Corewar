/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:48:45 by sdagger           #+#    #+#             */
/*   Updated: 2020/10/03 22:48:46 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "corewar_errors.h"
# include "op.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

# define OP_CODE_LEN	1
# define ARGS_CODE_LEN	1
# define REG_LEN		1

# define LIVE_LOG			1
# define CYCLE_LOG			2
# define OP_LOG				4
# define DEATH_LOG			8
# define PC_MOVEMENT_LOG	16

static unsigned char	g_arg_code[3] = {
	T_REG,
	T_DIR,
	T_IND
};

typedef enum
{
	FALSE,
	TRUE
}	t_bool;

typedef struct			s_player
{
	int					id;
	char				*name;
	char				*comment;
	int					code_size;
	uint8_t				*code;
	size_t				current_lives_num;
	size_t				previous_lives_num;
	ssize_t				last_live;
	struct s_player		*next;
}						t_player;

typedef struct			s_cursor
{
	unsigned int		id;
	t_bool				carry;
	unsigned char		op_code;
	ssize_t				last_live;
	int					cycles_to_exec;
	unsigned char		args_types[3];
	int					pc;
	unsigned int		step;
	int					reg[REG_NUMBER];
	t_player			*player;
	struct s_cursor		*next;
}						t_cursor;

typedef struct			s_vm
{
	unsigned char		arena[MEM_SIZE];
	t_player			*players[MAX_PLAYERS];
	int					players_num;
	t_player			*last_alive;
	t_cursor			*cursors;
	size_t				cursors_num;
	size_t				lives_num;
	ssize_t				cycles;
	ssize_t				cycles_to_die;
	ssize_t				cycles_after_check;
	size_t				checks_num;
	ssize_t				dump_cycle;
	int					dump_print_mode;
	ssize_t				show_cycle;
	int					show_print_mode;
	t_bool				display_aff;
	int					log;
}						t_vm;

typedef struct			s_op
{
	char				*name;
	unsigned char		code;
	unsigned char		args_num;
	t_bool				args_types_code;
	unsigned char		args_types[3];
	t_bool				modify_carry;
	unsigned char		t_dir_size;
	unsigned int		cycles;
	void				(*func)(t_vm *, t_cursor *);

}						t_op;

void					err_func();

void					op_live(t_vm *vm, t_cursor *pc);
void					op_ld(t_vm *vm, t_cursor *pc);
void					op_st(t_vm *vm, t_cursor *pc);
void					op_add(t_vm *vm, t_cursor *pc);
void					op_sub(t_vm *vm, t_cursor *pc);
void					op_and(t_vm *vm, t_cursor *cursor);
void					op_or(t_vm *vm, t_cursor *cursor);
void					op_xor(t_vm *vm, t_cursor *cursor);
void					op_zjmp(t_vm *vm, t_cursor *cursor);
void					op_ldi(t_vm *vm, t_cursor *cursor);
void					op_sti(t_vm *vm, t_cursor *cursor);
void					op_fork(t_vm *vm, t_cursor *cursor);
void					op_lld(t_vm *vm, t_cursor *cursor);
void					op_lldi(t_vm *vm, t_cursor *cursor);
void					op_lfork(t_vm *vm, t_cursor *cursor);
void					op_aff(t_vm *vm, t_cursor *cursor);

static t_op				g_op[16] = {
	{
		.name = "live",
		.code = 0x01,
		.args_num = 1,
		.args_types_code = FALSE,
		.args_types = {T_DIR, 0, 0},
		.modify_carry = FALSE,
		.t_dir_size = 4,
		.cycles = 10,
		.func = &op_live
	},
	{
		.name = "ld",
		.code = 0x02,
		.args_num = 2,
		.args_types_code = TRUE,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.modify_carry = TRUE,
		.t_dir_size = 4,
		.cycles = 5,
		.func = &op_ld
	},
	{
		.name = "st",
		.code = 0x03,
		.args_num = 2,
		.args_types_code = TRUE,
		.args_types = {T_REG, T_REG | T_IND, 0},
		.modify_carry = FALSE,
		.t_dir_size = 4,
		.cycles = 5,
		.func = &op_st
	},
	{
		.name = "add",
		.code = 0x04,
		.args_num = 3,
		.args_types_code = TRUE,
		.args_types = {T_REG, T_REG, T_REG},
		.modify_carry = TRUE,
		.t_dir_size = 4,
		.cycles = 10,
		.func = &op_add
	},
	{
		.name = "sub",
		.code = 0x05,
		.args_num = 3,
		.args_types_code = TRUE,
		.args_types = {T_REG, T_REG, T_REG},
		.modify_carry = TRUE,
		.t_dir_size = 4,
		.cycles = 10,
		.func = &op_sub
	},
	{
		.name = "and",
		.code = 0x06,
		.args_num = 3,
		.args_types_code = TRUE,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.modify_carry = TRUE,
		.t_dir_size = 4,
		.cycles = 6,
		.func = &op_and
	},
	{
		.name = "or",
		.code = 0x07,
		.args_num = 3,
		.args_types_code = TRUE,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.modify_carry = TRUE,
		.t_dir_size = 4,
		.cycles = 6,
		.func = &op_or
	},
	{
		.name = "xor",
		.code = 0x08,
		.args_num = 3,
		.args_types_code = TRUE,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.modify_carry = TRUE,
		.t_dir_size = 4,
		.cycles = 6,
		.func = &op_xor
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.args_num = 1,
		.args_types_code = FALSE,
		.args_types = {T_DIR, 0, 0},
		.modify_carry = FALSE,
		.t_dir_size = 2,
		.cycles = 20,
		.func = &op_zjmp
	},
	{
		.name = "ldi",
		.code = 0x0A,
		.args_num = 3,
		.args_types_code = TRUE,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.modify_carry = FALSE,
		.t_dir_size = 2,
		.cycles = 25,
		.func = &op_ldi
	},
	{
		.name = "sti",
		.code = 0x0B,
		.args_num = 3,
		.args_types_code = TRUE,
		.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.modify_carry = FALSE,
		.t_dir_size = 2,
		.cycles = 25,
		.func = &op_sti
	},
	{
		.name = "fork",
		.code = 0x0C,
		.args_num = 1,
		.args_types_code = FALSE,
		.args_types = {T_DIR, 0, 0},
		.modify_carry = FALSE,
		.t_dir_size = 2,
		.cycles = 800,
		.func = &op_fork
	},
	{
		.name = "lld",
		.code = 0x0D,
		.args_num = 2,
		.args_types_code = TRUE,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.modify_carry = TRUE,
		.t_dir_size = 4,
		.cycles = 10,
		.func = &op_lld
	},
	{
		.name = "lldi",
		.code = 0x0E,
		.args_num = 3,
		.args_types_code = TRUE,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.modify_carry = TRUE,
		.t_dir_size = 2,
		.cycles = 50,
		.func = &op_lldi
	},
	{
		.name = "lfork",
		.code = 0x0F,
		.args_num = 1,
		.args_types_code = FALSE,
		.args_types = {T_DIR, 0, 0},
		.modify_carry = FALSE,
		.t_dir_size = 2,
		.cycles = 1000,
		.func = &op_lfork
	},
	{
		.name = "aff",
		.code = 0x10,
		.args_num = 1,
		.args_types_code = TRUE,
		.args_types = {T_REG, 0, 0},
		.modify_carry = FALSE,
		.t_dir_size = 4,
		.cycles = 2,
		.func = &op_aff
	}
};

t_player				*init_player(int id);
t_cursor				*init_cursor(t_player *player, int pc);
t_vm					*init_vm(void);
void					init_arena(t_vm *vi_ma);

void					free_players(t_player **players, int players_num);
void					free_cursors(t_cursor **list);
void					free_vi_ma(t_vm **vi_ma);

unsigned int			step_size(unsigned char arg_type, t_op *op);
unsigned int			calc_step(t_cursor *cursor, t_op *op);
int						calc_addr(int addr);

void					terminate(char *s);
char					get_byte(t_vm *vm, int pc, int step);
t_bool					check_tab(char c);
t_bool					check_integer(const char *str, t_bool strict);
t_player				*find_player(t_player *players_l, int id);

void					reset_lives_nums(t_vm *vm);
t_bool					is_died(t_vm *vm, t_cursor *cursor);
void					delete_died_cursors(t_vm *vm);
void					cycles_to_die_check(t_vm *vm);

void					log_cycle(ssize_t cycle);
void					log_pc_movements(unsigned char *arena,
						t_cursor *cursor);
void					log_cursor_death(t_vm *vm, t_cursor *cursor);
void					log_cycles_to_die(ssize_t cycles_to_die);

int						bytecode_to_int_utils(const unsigned char
						*arena, int addr, int size);
int						parse_int(int fd);
char					*parse_str(int fd, size_t len);
unsigned char			*parse_code(int fd, size_t len);
t_player				*parse_champion(char *filename, int id);

void					parse_dump(int *argc, char ***argv, t_vm *vi_ma);
void					parse_log(int *ac, char ***av, t_vm *vi_ma);
void					parse_show(int *argc, char ***argv, t_vm *vi_ma);
void					parse_aff(int *argc, char ***argv, t_vm *vi_ma);

void					print_intro(t_player **players, int players_num);
void					print_winner(t_vm *vm);
void					print_arena(unsigned char *arena, int print_mode);
void					print_help(void);

void					add_player(t_player **player_l, t_player *new);
void					parse_champion_filename(int *ac, char ***av,
						t_vm *vi_ma, t_player **player_l);
void					update_players(t_player *player_l);
void					set_players(t_vm *vi_ma, t_player *player_l);
void					args_parce(int ac, char **av, t_vm *vi_ma);

void					update_op_code(t_vm *vm, t_cursor *current);
void					move_cursor(t_cursor *cursor);
void					do_op(t_cursor *cursor, t_vm *vm);
void					in_cycle(t_vm *vm);
void					start(t_vm *vm);

void					parse_types_code(t_vm *vm, t_cursor *cursor, t_op *op);
t_bool					is_arg_types_valid(t_cursor *cursor, t_op *op);
t_bool					is_register(t_vm *vm, int pc, int step);
t_bool					is_args_valid(t_cursor *cursor, t_vm *vm, t_op *op);
t_bool					is_champ(const char *filename, const char *ext);
void					add_cursor(t_cursor **list, t_cursor *new);
void					set_cursors(t_vm *vm);
int						get_op_arg(t_vm *vm, t_cursor *cursor,
						unsigned char index, t_bool mod);
void					int_to_bytecode(unsigned char *arena, int addr,
						int value, int size);
t_cursor				*duplicate_cursor(t_cursor *cursor, int addr);
int						ft_abs(int number);

#endif

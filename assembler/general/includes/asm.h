/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:31:22 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/20 15:53:56 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "op.h"
# include "fcntl.h"
# define USAGE "Usage: ./asm file.s"
# define COLOR_RED              "\x1b[31m"
# define COLOR_GREEN    "\x1b[32m"
# define COLOR_YELLOW   "\x1b[33m"
# define COLOR_PINK             "\x1b[1;35m"
# define COLOR_BLUE             "\x1b[34m"
# define COLOR_MAGENTA  "\x1b[35m"
# define COLOR_CYAN             "\x1b[36m"
# define COLOR_RESET    "\x1b[0m"
# define C_REG 1
# define C_DIR 2
# define C_IND 3
/*
** t_asm structure
** fd - file descriptor
** tokens - list of tokens
** i - column of file
** row - row of file
*/

typedef struct	s_asm
{
	int					fd;
	unsigned			i;
	int					row;
	int					start;
	t_list				*tokens;
	unsigned char		*code;
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
	char				*line;
	char				**dline;
	char				**file;
	long				code_size;
	int					curr_start;
	char				prog_name_e;
	char				comment_e;
	t_list				*labels;
	t_list				*ref_labels;
}				t_asm;

/*
** t_asm functions
*/

void			del_tokens(void *list, size_t size);
t_asm			*init_asm(void);
void			free_asm(t_asm *sasm);

/*
** There are enum for possible types to tokens
*/

typedef			enum
{
	OPERATOR,
	COMMAND,
	STRING,
	REGISTER,
	SEPARATOR,
	LABEL,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	NEW_LINE,
	END
}				t_ctype;

/*
** t_token structure
*/

typedef struct	s_token
{
	char		*content;
	t_ctype		type;
	unsigned	i;
	unsigned	row;
}				t_token;

typedef struct	s_label
{
	char		*name;
	int			point;
}				t_label;

typedef struct	s_ref_label
{
	char		*name;
	int			start;
	int			end;
	t_ctype		type;
	int			comm_start;
}				t_ref_label;


/*
** service functions
*/

t_asm			*error_f(char *error, char init);

/*
** read_file
*/

void			read_file(t_asm *sasm, char *file);

/*
** write_file
*/

void write_file(t_asm *sasm, char *name);

/*
** process_file parsing
*/

int				is_whitespace(int c);
int				is_delimiter(int c);
void			skip_comment(t_asm *sasm, char *row);
void			skip_whitespace(t_asm *sasm, char *row);
void			process_file(t_asm *sasm);
void			parse_command(t_asm *sasm, char *row);
void			parse_string(t_asm *sasm, char *row);
void			parse_label(t_asm *sasm, char *row);
void			parse_newline(t_asm *sasm);
void			parse_separator(t_asm *sasm);
void			parse_token(t_asm *sasm, char *row);

/*
** process_file_extra (some service function)
*/

int				only_digit(t_asm *sasm, char *row);
int				is_register(t_asm *sasm, char *row);

/*
** process_file checking
*/

void			find_name_and_comment(t_list *list, void *stuff);
void			convert_tokens(t_asm *sasm, t_list *tokens);

/*
** t_token
*/

t_token			*init_token(t_asm *sasm, t_ctype type);
void			add_token(t_asm *sasm, t_token	*token);

/*
** some extended stuff
*/

int				nget_next_line(const int fd, char **line);
int32_t			ft_atoi32(const char *str);

void			print_token(t_list *list);

#endif
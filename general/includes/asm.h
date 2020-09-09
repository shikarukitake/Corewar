
#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "op.h"

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
	int					i;
	int					row;
	t_list				*tokens;
	char				*code;
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
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
	t_ctype		*type;
	unsigned	i;
	unsigned	row;

}				t_token;

/*
** service functions
*/

t_asm			*error_f(char *error, char init);

/*
** read_file
*/

void			read_file(t_asm *sasm);

/*
** write_file
*/

void			write_file(t_asm *sasm);

#endif

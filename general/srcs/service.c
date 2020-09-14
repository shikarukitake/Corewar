#include "asm.h"

void	write_col_row(t_asm *sasm, char const *error)
{
	char	*row;
	char	*col;

	row = ft_itoa(sasm->row);
	col = ft_itoa(sasm->i);
	if (!row || !col)
	{
		free_asm(sasm);
		if (row)
			free(row);
		if (col)
			free(col);
		ft_error_t("malloc when showing error");
	}
	write(2, "ERROR\n", 5);
	if (error)
		write(2, error, ft_strlen(error));
	write(2, "\nROW:", 5);
	write(2, row, ft_strlen(row));
	write(2, "\nCOL:", 5);
	write(2, col, ft_strlen(col));
	free(row);
	free(col);
	free_asm(sasm);
	exit(1);
}

t_asm	*error_f(char *error, char init)
{
	static t_asm	*sasm;

	if (init)
	{
		sasm = init_asm();
		return (sasm);
	}
	if (sasm->row >= 0 && sasm->i >= 0)
		write_col_row(sasm, error);
	free_asm(sasm);
	ft_error_t(error);
	return (NULL);
}

int		is_whitespace(int c)
{
	return (c == '\t' ||
			c == '\v' ||
			c == '\f' ||
			c == '\r' ||
			c == ' ');
}

int		is_delimiter(int c)
{
	return (c == '\0'
			|| c == '\n'
			|| is_whitespace(c)
			|| c == COMMAND_CHAR
			|| c == '\"'
			|| c == DIRECT_CHAR
			|| c == SEPARATOR_CHAR
			|| c == COMMENT_CHAR
			|| c == ALT_COMMENT_CHAR);
}

void	skip_whitespace(t_asm *sasm, char *row)
{
	while (is_whitespace(row[sasm->i]))
		sasm->i++;
}

void	skip_comment(t_asm *sasm, char *row)
{
	if (row[sasm->i] == COMMENT_CHAR
		|| row[sasm->i] == ALT_COMMENT_CHAR)
		while (row[sasm->i] && row[sasm->i] != '\n')
			sasm->i++;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 12:37:25 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 16:32:49 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_colrow(const char *error, const char *row, const char *col)
{
	write(2, "ERROR\n", 6);
	if (error)
		write(2, error, ft_strlen(error));
	write(2, "\nROW:", 5);
	write(2, row, ft_strlen(row));
	write(2, "\nCOL:", 5);
	write(2, col, ft_strlen(col));
	write(2, "\n", 1);
}

void	write_col_row(t_asm *sasm, char const *error)
{
	char	*row;
	char	*col;

	row = ft_itoa(sasm->row + 1);
	col = ft_itoa(sasm->i + 1);
	if (!row || !col)
	{
		free_asm(sasm);
		if (row)
			free(row);
		if (col)
			free(col);
		ft_error_t("malloc when showing error");
	}
	write_colrow(error, row, col);
	free(row);
	free(col);
	free_asm(sasm);
	exit(1);
}

t_asm	*error_f(char *error, char init)
{
	static t_asm	*sasm;

	if (init == 1)
	{
		sasm = init_asm();
		return (sasm);
	}
	if (init == 2)
		write_col_row(sasm, error);
	free_asm(sasm);
	if (init == 0)
		ft_error_t(error);
	return (NULL);
}

void	error_token(char *error, t_token *token)
{
	char	*row;
	char	*col;

	row = ft_itoa(token->row + 1);
	col = ft_itoa(token->i + 1);
	if (!row || !col)
	{
		if (row)
			free(row);
		if (col)
			free(col);
		error_f("malloc when showing error", 0);
	}
	write_colrow(error, row, col);
	free(row);
	free(col);
	error_f(NULL, -1);
	exit(1);
}

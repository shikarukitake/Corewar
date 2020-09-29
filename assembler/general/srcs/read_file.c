/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 12:37:20 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/20 12:37:20 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	malloc_file(t_asm *sasm, char *file)//todo maybe don't int
{
	int	i;

	i = 0;
	sasm->fd = open(file, O_RDONLY);
	if (sasm->fd < 0)
		error_f("can't open file", 0);
	while (nget_next_line(sasm->fd, &(sasm->line)) > 0)
	{
		i++;
		if (sasm->line)
			ft_strdel(&(sasm->line));
	}
	if (i == 0)
		error_f("empty_file", 0);
	sasm->file = malloc(sizeof(char*) * (i + 1));
	if (sasm->file == NULL)
		error_f("malloc_file malloc", 0);
	sasm->file[i] = NULL;
	close(sasm->fd);
}

void	read_file(t_asm *sasm, char *file)
{
	int		i;

	i = 0;
	malloc_file(sasm, file);
	sasm->fd = open(file, O_RDONLY);
	if (sasm->fd < 0)
		error_f("can't open file", 0);
	while (nget_next_line(sasm->fd, &(sasm->line)) > 0)
	{
		if (sasm->line == NULL)
			error_f("malloc nget_next_line", 0);
		sasm->file[i] = sasm->line;
		sasm->line = NULL;
		i++;
	}
	if (sasm->line)
		free(sasm->line);
	close(sasm->fd);
}//todo get next line when in end of file new line without any characters
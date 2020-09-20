/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 12:37:45 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/20 16:21:06 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_new_name(char *name)
{
	char	*new_name;
	int		i;

	i = ft_strlen(name);
	while (name[i] != '.')
		i--;
	new_name = malloc(sizeof(char) * (i + 5));
	if (new_name == NULL)
		error_f("get_new_name malloc", 0);
	new_name[i--] = 0;
	while (i >= 0)
	{
		new_name[i] = name[i];
		i--;
	}
	ft_strcat(new_name, ".cor");
	return (new_name);
}

void	write_null(int fd)
{
	int		i;

	i = 0;
	while (i != 4)
	{
		ft_putchar_fd(0, fd);
		i++;
	}
}

void	write_exec_code_size(int fd, t_asm *sasm)
{
	unsigned	code;
	int			size;

	code = sasm->i;
	size = 4;
	while (size != 0)
	{
		ft_putchar_fd(code >> (8 * (size - 1)), fd);
		size--;
	}
}

void	write_all(int fd, t_asm *sasm)
{
	ft_putchar_fd(0, fd);
	ft_putchar_fd((char)234, fd);
	ft_putchar_fd((char)131, fd);
	ft_putchar_fd((char)243, fd);
	write(fd, sasm->prog_name, PROG_NAME_LENGTH);
	write_null(fd);
	write_exec_code_size(fd, sasm);
	write(fd, sasm->comment, COMMENT_LENGTH);
	write_null(fd);
}

void	write_file(t_asm *sasm, char *name)
{
	int		i;
	int		fd;
	char	*new_name;

	i = 0;
	new_name = get_new_name(name);

	fd = open(new_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(new_name);
		error_f("Can't open file to writing", 0);
	}
	write_all(fd, sasm);
	write(fd, sasm->code, sasm->i);
	close(fd);
	ft_printf("Writing output program to ");
	ft_printf(new_name);
	ft_printf("\n");
	free(new_name);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_gnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 12:37:32 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 14:06:58 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include "asm.h"

void ft_line_maker_part(char **help, char **line, size_t len)
{
	char	*iter;

	*line = ft_strsub(*help, 0, len + 1);//todo if can't malloc
	if (*line == NULL)
		error_f("gnl line_maker strsub", 0);
	iter = ft_strsub(*help, len + 1, ft_strlen(*help) - len);
	if (iter == NULL)
		error_f("gnl line_maker strsub", 0);
	free(*help);
	*help = ft_strdup(iter);
	if (*help == NULL)
		error_f("gnl line_maker strdup", 0);
	free(iter);
}

static int	ft_line_maker(const int fd, char **help, char **line)
{
	size_t	len;

	len = 0;
	while (help[fd][len] != '\0' && help[fd][len] != '\n')
		len++;
	if (help[fd][len] == '\n')
		ft_line_maker_part(&help[fd], line, len);
	else if (help[fd][len] == '\0')
	{
		*line = ft_strdup(help[fd]);
		if (*line == NULL)
			error_f("gnl line_maker strdup", 0);
		ft_strdel(&help[fd]);
	}
	return (1);
}

int			nget_next_line(const int fd, char **line)
{
	static char	*help[OPEN_MAX];
	char		buff[BUFF_SIZE + 1];
	char		*iter;
	int			rdr;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((rdr = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[rdr] = '\0';
		if (help[fd] == NULL)
			if ((help[fd] = ft_strnew(1)) == NULL)
				error_f("gnl strnew malloc", 0);
		if ((iter = ft_strjoin(help[fd], buff)) == NULL)
			error_f("gnl strjoin", 0);
		free(help[fd]);
		help[fd] = iter;
		if (ft_strchr(help[fd], '\n'))
			break ;
	}
	if (rdr < 0)
		return (-1);
	if (rdr == 0 && (help[fd] == NULL || help[fd][0] == '\0'))
		return (0);
	return (ft_line_maker(fd, help, line));
}

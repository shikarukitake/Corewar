/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsedgeki <lsedgeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:56:35 by lsedgeki          #+#    #+#             */
/*   Updated: 2020/09/29 12:01:33 by lsedgeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>

int				bytecode_to_int(const unsigned char *bytecode, size_t size)
{
	int		result;
	t_bool	sign;
	int		i;

	result = 0;
	sign = (t_bool)(bytecode[0] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((bytecode[size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += bytecode[size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

int				parse_int(int fd)
{
	ssize_t			size;
	unsigned char	buffer[4];

	size = read(fd, &buffer, 4);
	if (size == -1)
		terminate(READ_FILE);
	if (size < 4)
		terminate(INVALID_FILE);
	return (bytecode_to_int(buffer, 4));
}

char			*parse_str(int fd, size_t len)
{
	ssize_t	size;
	char	*buffer;

	if (!(buffer = ft_strnew(len)))
		terminate(STR_INIT);
	size = read(fd, buffer, len);
	if (size == -1)
		terminate(READ_FILE);
	if (size < (ssize_t)len)
		terminate(INVALID_FILE);
	return (buffer);
}

unsigned char	*parse_code(int fd, size_t len)
{
	ssize_t	size;
	uint8_t	*buffer;
	uint8_t	byte;

	if (!(buffer = malloc(len)))
		terminate(CODE_INIT);
	size = read(fd, buffer, len);
	if (size == -1)
		terminate(READ_FILE);
	if (size < (ssize_t)len || read(fd, &byte, 1) != 0)
		terminate(INVALID_FILE);
	return (buffer);
}

t_player		*parse_champion(char *filename, int id)
{
	t_player	*player;
	int			fd;

	player = init_player(id);
	if ((fd = open(filename, O_RDONLY)) < 0)
		terminate(OPEN_FILE);
	if (parse_int(fd) != COREWAR_EXEC_MAGIC)
		terminate(INVALID_MAGIC);
	player->name = parse_str(fd, PROG_NAME_LENGTH);
	if (parse_int(fd) != 0)
		terminate(NO_NULL);
	if ((player->code_size = parse_int(fd)) < 0 ||
		player->code_size > CHAMP_MAX_SIZE)
		terminate(INVALID_CODE_SIZE);
	player->comment = parse_str(fd, COMMENT_LENGTH);
	if (parse_int(fd) != 0)
		terminate(NO_NULL);
	player->code = parse_code(fd, (size_t)player->code_size);
	return (player);
}

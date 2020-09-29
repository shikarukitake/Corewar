#include "libft.h"

void	error_f(char *text, int init)
{
	exit(1);
}

int		nget_next_line(const int fd, char **line)
{
	static char	*file
	char		buff[BUFF_SIZE + 1];
	int			ret;

	if (fd < 0 || line == NULL)
		error_f("nget_next_line fd < 0 || line==NULL", 0);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
}

int		main(void)
{



	return (0);
}
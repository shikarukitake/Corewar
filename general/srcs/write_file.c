#include "asm.h"

char	*get_new_name(char *name)
{
	char	*new_name;
	int		i;

	i = 0;
	while (name[i] != '.')
		i++;
	new_name = malloc(sizeof(char) * (i + 5));
	if (new_name == NULL)
		error_f("get_new_name malloc", 0);
	i = 0;
	while (name[i] != '.')
	{
		new_name[i] = name[i];
		i++;
	}
	new_name[i] = 0;
	ft_strcat(new_name, ".cor");
	return (new_name);
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
	write(fd, sasm->code, sasm->i);
	close(fd);
	ft_printf("Writing output program to ");
	ft_printf(new_name);
	ft_printf("\n");
	free(new_name);
}
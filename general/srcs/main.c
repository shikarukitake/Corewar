#include "asm.h"

int		main(int ac, char **av)
{
	t_asm	*sasm;

	sasm = error_f(NULL, 1);
	if (ac != 2)
		error_f(USAGE, 0);
	read_file(sasm, av[1]);
	process_file(sasm);
	write_file(sasm);
	free_asm(sasm);
	ft_printf(COLOR_PINK "programm end" COLOR_RESET);
	ft_printf("%d", T_DIR | T_IND | T_REG);
	exit(0);
	return (0);
}
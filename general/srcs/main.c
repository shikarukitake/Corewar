#include "asm.h"

int		main(void)
{
	t_asm	*sasm;

	sasm = error_f(NULL, 1);
	read_file(sasm);
	write_file(sasm);
	free_asm(sasm);
	exit(0);
	return (0);	
}
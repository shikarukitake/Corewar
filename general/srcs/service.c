#include "asm.h"

t_asm	*error_f(char *error, char init)
{
	static t_asm	*sasm;

	if (init)
	{
		sasm = init_asm();
		return (sasm);
	}
	free_asm(sasm);
	ft_error_t(error);
	return (NULL);
}
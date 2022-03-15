#include <minishell.h>

int	unset(char **arg)
{
	int	i;

	i = 0;
	while (arg[++i])
		remove_lst(arg[i]);
	return (0);
}

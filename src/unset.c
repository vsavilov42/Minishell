#include <minishell.h>

int	unset(char **arg)
{
	int	i;

	i = 0;
	while (arg[++i])
	{
		printf("%s\n", arg[i]);
		remove_lst(arg[i]);
	}
	return (0);
}

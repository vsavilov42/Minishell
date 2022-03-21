#include <minishell.h>

int	ft_unset(char **arg)
{
	int	i;

	i = 0;
	while (arg[++i])
		remove_lst(arg[i]);
	return (0);
}

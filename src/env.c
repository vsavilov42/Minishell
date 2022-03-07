#include <minishell.h>

int	env(char **arg)
{
	int	i;
	t_envlst	*envlst;

	i = -1;
	envlst = g_built.env;
	if (arg[1] != NULL)
		return (1);
	while (envlst)
	{
		if (envlst->value)
		{
			ft_putstr_fd(envlst->name, 1);
			write(1, "=", 1);
			ft_putstr_fd(envlst->value, 1);
			write(1, "\n", 1);
		}
		envlst = envlst->next;
	}
	return (0);
}

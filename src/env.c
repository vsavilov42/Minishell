#include <minishell.h>

int	env(char **arg)
{
	int	i;
	t_envlst	envlst;

	i = -1;
	envlst = *g_built.env;
	if (arg[1] != NULL)
		return (1);
	while (envlst.next)
	{
		ft_putstr_fd(envlst.name, 1);
		write(1, "=", 1);
		ft_putstr_fd(envlst.value, 1);
		write(1, "\n", 1);
		//printf("ENV[NAME] -> %s\n", envlst->name);
		//printf("%s\n", envlst->value);
		envlst = *envlst.next;
	}
	return (0);
}

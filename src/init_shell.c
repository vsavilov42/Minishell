#include <minishell.h>

void	init_minishell(void)
{
	get_env();
}

void	get_env(void)
{
	extern char **environ;
	int		i;

	t_envlst	*envlst;
	i = -1;
	envlst = NULL;
	while (environ[++i])
		envlst_add_back(&envlst, new_envlst(environ[i]));
	g_built.env = envlst;
}

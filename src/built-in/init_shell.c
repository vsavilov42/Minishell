#include <minishell.h>

static void start_env(char *shell_lvl, char *pwd);

void	init_minishell(void)
{
	get_env();
}

void	get_env(void)
{
	extern char	**environ;
	int		i;
	char		*pwd;
	char		*shell_lvl;

	i = -1;
	g_sh.env = (t_envlst **)ft_calloc(1, (sizeof(t_envlst *) * 10));
	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!g_sh.env || !pwd)
		return ;
	shell_lvl = ft_strdup("SHLVL=1");
	if (*environ)
	{
		while (environ[++i])
			envlst_add_back(g_sh.env, new_envlst(environ[i]));
		envlst_add_back(g_sh.env, new_envlst(shell_lvl));
		//shell_lvl
	}
	else
		start_env(shell_lvl, pwd);
	free(pwd);
	free(shell_lvl);
}

static void start_env(char *shell_lvl, char *pwd)
{
	char	*tmp;

	tmp = NULL;
	if (getcwd(pwd, PATH_MAX))
	{
		tmp = ft_strjoin("PWD=", pwd);
		envlst_add_back(g_sh.env, new_envlst(tmp));
	}
	envlst_add_back(g_sh.env, new_envlst(shell_lvl));
	free(tmp);
}

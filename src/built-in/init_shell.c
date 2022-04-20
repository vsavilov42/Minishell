#include <minishell.h>

void	init_minishell(void)
{
	get_env();
//	get_cmds();
}

void	get_cmds(void)
{
	t_bt_lst	*bt;

	bt = (t_bt_lst *)malloc(sizeof(t_bt_lst));
	add_bt(bt, "echo", ft_echo);
	add_bt(bt, "cd", ft_cd);
	add_bt(bt, "pwd", ft_pwd);
	add_bt(bt, "export", ft_export);
	add_bt(bt, "unset", ft_unset);
	add_bt(bt, "env", ft_env);
	add_bt(bt, "exit", ft_exit);
	g_sh.bt = bt;
}

void	get_env(void)
{
	extern char **environ;
	int		i;
	char		*pwd;

	t_envlst	*envlst;
	pwd = malloc(sizeof(char) * PATH_MAX);
	i = -1;
	envlst = NULL;
	while (environ[++i])
		envlst_add_back(&envlst, new_envlst(environ[i]));
	if (envlst == NULL)
	{
		envlst = new_envlst_only_name("PWD");
		envlst->value = getcwd(pwd, PATH_MAX);
	}
	free(pwd);
	g_sh.env = envlst;
}

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
	add_bt(bt, "echo", echo);
	add_bt(bt, "env", env);
	add_bt(bt, "cd", cd);
	add_bt(bt, "pwd", pwd);
	add_bt(bt, "export", export);
	add_bt(bt, "unset", unset);
	add_bt(bt, "exit", bt_exit);
	g_built.bt = bt;
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
	g_built.env = envlst;
}

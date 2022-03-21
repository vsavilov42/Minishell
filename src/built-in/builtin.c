#include <minishell.h>

void	add_bt(t_bt_lst *bt, char *name, int (*f)(char **))
{
	t_bt_lst	*new;
	t_bt_lst	*tmp;

	new = (t_bt_lst *)malloc(sizeof(t_bt_lst));
	if (!new)
		return ;
	new->cmd = name;
	new->f = f;
	new->next = NULL;
	if (!bt)
	{
		tmp = bt;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		bt = new;
}

void	builtin(char **arg)
{
	int	i;
	char	**cmds;

	i = -1;
	cmds = builtin_cmd();
	while (cmds[++i])
	{
		if (!same_strcmp(cmds[i], arg[0]))
			call_built(arg);
	}
	free_split(cmds);
}

void	call_built(char **cmd)
{
	if (!same_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	if (!same_strcmp(cmd[0], "cd"))
		ft_cd(cmd);
	if (!same_strcmp(cmd[0], "pwd"))
		ft_pwd(cmd);
	if (!same_strcmp(cmd[0], "export"))
		ft_export(cmd);
	if (!same_strcmp(cmd[0], "unset"))
		ft_unset(cmd);
	if (!same_strcmp(cmd[0], "env"))
		ft_env(cmd);
	if (!same_strcmp(cmd[0], "exit"))
		ft_exit(cmd);
}

char	**builtin_cmd(void)
{
	char	**cmds;

	cmds = (char **)malloc(sizeof(char *) * (8));
	cmds[0] = ft_strdup("echo");
	cmds[1] = ft_strdup("cd");
	cmds[2] = ft_strdup("pwd");
	cmds[3] = ft_strdup("export");
	cmds[4] = ft_strdup("unset");
	cmds[5] = ft_strdup("env");
	cmds[6] = ft_strdup("exit");
	cmds[7] = NULL;
	return (cmds);
}

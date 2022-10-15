#include <minishell.h>

static int	count_env(t_envlst *envlst)
{
	int	n;

	n = 0;
	while (envlst)
	{
		n++;
		envlst = envlst->next;
	}
	return (n);
}	

static char	**env_in_char(void)
{
	t_envlst	*lst;
	char	**env;
	char	*tmp;
	int	i;

	lst = *g_sh.env;
	env = (char **)malloc(sizeof(char *) * (count_env(lst) + 1));
	i = 0;
	while (lst)
	{
		tmp = ft_strjoin(lst->name, "=");
		env[i] = ft_strjoin(tmp, lst->value);
		i++;
		free(tmp);
		lst = lst->next;
	}
	return (env);
}

static char	*get_path(char *cmd, char *path)
{
	char	**envtmp;
	char	*tmp;
	int	i;

	envtmp = ft_split(path, ':');
	tmp = ft_strjoin("/", cmd);
	i = -1;
	while (envtmp[++i])
		if (access(ft_strjoin(envtmp[i], tmp), X_OK) == 0)
			return (ft_strjoin(envtmp[i], tmp));
	ft_putstr_fd("Error: Command not found\n", STDERR_FILENO);
	exit(CMD_NOTFOUND);
	return (NULL);
}

void	execve_cmd(t_cmd *cmd)
{
	char	*cpath;
	char	*path;

	if (*cmd->cmd[0] == '/' || !ft_strncmp(cmd->cmd[0], "~/", 2)
		|| !ft_strncmp(cmd->cmd[0], "./", 2)
		|| !ft_strncmp(cmd->cmd[0], "../", 3))
		cpath = cmd->cmd[0];
	else
	{
		path = return_value("PATH");
		if (!path)
		{
			ft_putstr_fd(cmd->cmd[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exit(CMD_NOTFOUND);
		}
		cpath = get_path(cmd->cmd[0], path);
	}
	execve(cpath, cmd->cmd, env_in_char());
	exit(perror_ret(cpath, 127));
}

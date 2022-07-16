/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_analyze.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:56:20 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/07/16 22:40:15 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	standard_command(char **cmd)
{
	(void)cmd;
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	exec->pid = fork();
	if (exec->pid > 0)
		write(2, "Error: pid failure\n", 19);
}

int	free_str(char *cmd)
{
	free(cmd);
	return (0);
}

int	is_builtin(char **cmd)
{
	char *tmp;

	tmp = strtolow(*cmd);
	if (!same_strcmp(tmp, "echo"))
		return (free_str(tmp));
	if (!same_strcmp(tmp, "cd"))
		return (free_str(tmp));
	if (!same_strcmp(tmp, "pwd"))
		return (free_str(tmp));
	if (!same_strcmp(tmp, "export"))
		return (free_str(tmp));
	if (!same_strcmp(tmp, "unset"))
		return (free_str(tmp));
	if (!same_strcmp(tmp, "env"))
		return (free_str(tmp));
	if (!same_strcmp(tmp, "exit"))
		return (free_str(tmp));
	free(tmp);
	return (1);
}

int	count_env(t_envlst *envlst)
{
	int	num_env;

	num_env = 0;
	while (envlst)
	{
		num_env++;
		envlst = envlst->next;
	}
	return (num_env);
}

char	**env_pointer(void)
{
	t_envlst	*envlst;
	char		**env;
	char		*tmp;
	int		i;

	if (!g_sh.env)
		return (NULL);
	envlst = *g_sh.env;
	env = (char **)malloc(sizeof(char *) * count_env(envlst));
	i = 0;
	while (envlst)
	{
		tmp = ft_strjoin(envlst->name, "=");
		env[i] = ft_strjoin(tmp, envlst->value);
		i++;
		free(tmp);
		envlst = envlst->next;
	}
	return (env);
}

void	command_path(t_cmd *cmd, char *path_line)
{
	char	**envtmp;
	char	*tmp;
	int	i;

	envtmp = ft_split(path_line, ':');
	tmp = ft_strjoin("/", *cmd->argv);
	i = -1;
	while (envtmp[++i])
		if (access(ft_strjoin(envtmp[i], tmp), X_OK))
			cmd->cmd_path = ft_strjoin(envtmp[i], tmp);
	if (!cmd->cmd_path)
		ft_putstr_fd("Error: Command not found\n", 2);
}

char	**create_path(t_cmd *cmd)
{
	char	**env;
	char	*path_line;
	int	i;

	env = env_pointer();
	i = -1;
	if (**cmd->argv == '/' || **cmd->argv == '.' || access(*cmd->argv, X_OK) == 0)
		cmd->cmd_path = *cmd->argv;
	else
	{
		while (env[++i])
		{
			if (!same_strcmp("PATH=", env[i]))
				path_line = ft_substr(env[i], 5, ft_strlen(env[i]));
			if (!path_line)
				{
					ft_putstr_fd("Error: Path not found\n", 2);
					return (NULL);
				}
		}
		command_path(cmd, path_line);
	}
	return (env);
}

void	exec_one_command(t_cmd *cmds)
{
	if (!is_builtin(cmds->argv))
		builtin(cmds->argv);
	//else if (!is_heredoc(cmds->argv))
}

void	command_exec(t_cmd *cmds)
{
	t_cmd *tmp;

	tmp = cmds;
	if (cmds->next == NULL)
		exec_one_command(cmds);
	else
		while (tmp)
		{
			printf("patata");
			if (!same_strcmp(cmds->argv[0], "<<"))
				printf("heredoc_handler\n");
			builtin(tmp->argv);
			//standard_command(tmp->argv);
			tmp = tmp->next;
		}
}

void	command_analyze(t_cmd *cmds)
{
	g_sh.cmd = cmds;
	command_exec(cmds);
}

// | exec the last command without saving fd
// > redirect output command, create new one if doesn't exist. if exist, rm and create.
// >> creates the file if doesn't exist. if exist add the content.
// < redirect input command
// << heredoc

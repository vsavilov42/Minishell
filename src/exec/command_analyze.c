/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_analyze.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:56:20 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/05/30 13:29:40 by Vsavilov         ###   ########.fr       */
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
	envlst = g_sh.env;
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

void	exec_one_cmd_no_builtin(char **cmd)
{
	char **env;

	env = env_pointer();
	printf("%s\n", *env);
	free_split(env);
	(void)cmd;
}

void	exec_one_command(t_cmd *cmds)
{
	if (!is_builtin(cmds->argv))
		builtin(cmds->argv);
	//else if (!is_heredoc(cmds->argv))
	else
		exec_one_cmd_no_builtin(cmds->argv);
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
	command_exec(cmds);
}

// | exec the last command without saving fd
// > redirect output command, create new one if doesn't exist. if exist, rm and create.
// >> creates the file if doesn't exist. if exist add the content.
// < redirect input command
// << heredoc

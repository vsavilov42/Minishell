/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:40:07 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/05 14:28:53 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_builtin(t_builtin **bt, char *name, int (*f)(char **))
{
	t_builtin	*new;
	t_builtin	*tmp;

	new = (t_builtin *)malloc(sizeof(t_builtin));
	if (!new)
		perror_ret("malloc", 1);
	new->name = name;
	new->f = f;
	new->next = NULL;
	if (*bt)
	{
		tmp = *bt;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*bt = new;
}

t_builtin	*init_builtin(void)
{
	t_builtin	*bt;

	bt = NULL;
	add_builtin(&bt, "echo", ft_echo);
	add_builtin(&bt, "pwd", ft_pwd);
	add_builtin(&bt, "cd", ft_cd);
	add_builtin(&bt, "export", ft_export);
	add_builtin(&bt, "unset", ft_unset);
	add_builtin(&bt, "env", ft_env);
	add_builtin(&bt, "exit", ft_exit);
	return (bt);
}

void	builtin(char **arg)
{
	int		i;
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

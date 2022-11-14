/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   into_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:43:21 by vsavilov          #+#    #+#             */
/*   Updated: 2022/11/14 12:43:38 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exec_child_process(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror_ret("fork", 1);
	if (pid > 0)
	{
		signal_ignore();
		if (!cmd->sfd->in_out[WRITE_END])
			g_sh.gpid = pid;
	}
	else
	{
		signal_child();
		g_sh.child = TRUE;
		builtin_inpipes(cmd);
		if (redir_cmd(cmd, 0))
			exit(EXIT_FAILURE);
		execve_cmd(cmd);
	}
	return (FALSE);
}

static int	builtin_nopipes(t_cmd *cmd)
{
	t_builtin	*bt;

	if (!cmd->sfd->in_out[READ_END] && !cmd->sfd->in_out[WRITE_END])
	{
		bt = g_sh.builtin;
		while (bt)
		{
			if (!same_strcmp(cmd->cmd[0], bt->name))
			{
				if (redir_cmd(cmd, 1))
					return (-1);
				g_sh.status = bt->f(cmd->cmd);
				dup2(g_sh.fd_bio[0], STDIN_FILENO);
				dup2(g_sh.fd_bio[1], STDOUT_FILENO);
				return (1);
			}
			bt = bt->next;
		}
	}
	return (0);
}

static int	empty_cmd(t_cmd *cmd)
{
	pid_t	pid;

	if (!cmd->cmd[0])
	{
		pid = fork();
		if (pid == -1)
			perror_ret("fork", 1);
		if (pid > 0)
		{
			if (!cmd->sfd->in_out[WRITE_END])
				g_sh.gpid = pid;
			return (TRUE);
		}
		else
		{
			if (redir_cmd(cmd, TRUE))
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
	}
	else if (cmd->cmd[0][0] == '\0')
		return (perror_ret(" : command not found\n", 1));
	return (FALSE);
}

int	into_exec_cmd(t_cmd *cmd)
{
	int	result;

	if (cmd->ncmd < 0)
		return (TRUE);
	if (empty_cmd(cmd))
		return (FALSE);
	result = builtin_nopipes(cmd);
	if (result != 0)
	{
		if (result)
			return (FALSE);
		if (!result)
			return (TRUE);
	}
	exec_child_process(cmd);
	return (FALSE);
}

int	exec_pipe(t_ast *ast)
{
	int	fd[2];
	int	io_pipe[2];

	if (pipe(fd) == -1)
		perror_ret("pipe", 1);
	io_pipe[WRITE_END] = fd[WRITE_END];
	io_pipe[READ_END] = fd[READ_END];
	exec_cmd(ast->left, init_sfd(FALSE, TRUE, fd, io_pipe[READ_END]));
	ast = ast->right;
	while (ast && astree_get_type(ast) == NODE_PIPE)
	{
		close(io_pipe[WRITE_END]);
		if (pipe(fd) == -1)
			perror_ret("pipe", 1);
		io_pipe[WRITE_END] = fd[WRITE_END];
		exec_cmd(ast->left, init_sfd(TRUE, TRUE, fd, io_pipe[READ_END]));
		close(io_pipe[READ_END]);
		ast = ast->right;
	}
	io_pipe[READ_END] = fd[READ_END];
	exec_cmd(ast, init_sfd(TRUE, FALSE, fd, io_pipe[READ_END]));
	close(io_pipe[WRITE_END]);
	close(io_pipe[READ_END]);
	return (FALSE);
}

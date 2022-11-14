/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_astree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:56:20 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/11/14 12:41:20 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	zombies_process(void)
{
	pid_t	pid;
	int		status;

	status = 0;
	while (TRUE)
	{
		pid = waitpid(-1, &status, 0);
		if (pid <= 0)
			break ;
		if (pid == g_sh.gpid)
		{
			if (WIFEXITED(status))
				g_sh.status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_sh.status = status_exit(status);
		}
	}
}

int	exec_cmd(t_ast	*ast, t_pipe *sfd)
{
	t_cmd		cmd;
	t_nodetype	type;

	if (!ast)
		return (FALSE);
	type = astree_get_type(ast);
	if (type == NODE_CMD)
	{
		sfd->redir = ast->left;
		init_cmd(&cmd, sfd, ast);
		into_exec_cmd(&cmd);
		free_exec_cmd(&cmd);
	}
	return (FALSE);
}

static int	exec_job(t_ast *ast)
{
	if (!ast)
		return (FALSE);
	if (astree_get_type(ast) == NODE_PIPE)
		exec_pipe(ast);
	else
		exec_cmd(ast, init_sfd(FALSE, FALSE, 0, 0));
	zombies_process();
	return (FALSE);
}

static int	exec_and_or(t_ast *ast)
{
	t_nodetype	type;

	if (!ast)
		return (FALSE);
	type = astree_get_type(ast);
	if (type == NODE_AND)
	{
		exec_and_or(ast->left);
		if (g_sh.status == 0)
			exec_and_or(ast->right);
	}
	else if (type == NODE_OR)
	{
		exec_and_or(ast->left);
		if (g_sh.status != 0)
			exec_and_or(ast->right);
	}
	else if (type == NODE_SEQ)
	{
		exec_and_or(ast->left);
		exec_and_or(ast->right);
	}
	else
		exec_job(ast);
	return (FALSE);
}

int	exec_astree(t_ast *ast)
{
	if (!ast)
		return (FALSE);
	if (astree_get_type(ast) == NODE_SEQ)
	{
		exec_and_or(ast->left);
		exec_astree(ast->right);
	}
	else
		exec_and_or(ast);
	return (FALSE);
}

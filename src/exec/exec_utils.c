#include <minishell.h>

static int	init_subcmd(t_cmd *cmd, t_ast *ast)
{
	int	i;
	int	ln;
	t_ast	*tmp;

	tmp = ast;
	i = 0;
	while (tmp && (astree_get_type(tmp) == NODE_ARG || astree_get_type(tmp) == NODE_CMD))
	{
		tmp = tmp->right;
		i++;
	}
	cmd->cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cmd->cmd)
		perror_ret("malloc", 1);
	tmp = ast;
	i = 0;
	while (tmp && (astree_get_type(tmp) == NODE_ARG
		|| astree_get_type(tmp) == NODE_CMD))
	{
		ln = ft_strlen(tmp->data);
		cmd->cmd[i] = (char *)malloc(sizeof(char *) * (ln + 1));
		ft_strcpy(cmd->cmd[i], tmp->data);
		tmp = tmp->right;
		i++;
	}
	cmd->cmd[i] = NULL;
	cmd->ncmd = i;
	return (FALSE);
}

void	init_cmd(t_cmd *cmd, t_pipe *sfd, t_ast *ast)
{
	if (!ast || astree_get_type(ast) != NODE_CMD)
	{
		cmd->ncmd = 0;
		return ;
	}
	if (!ast->data)
	{
		cmd->ncmd = 0;
		cmd->cmd = (char **)malloc(sizeof(char *));
		if (!cmd->cmd)
			perror_ret("malloc", 1);
		cmd->cmd[0] = NULL;
		cmd->sfd = sfd;
		return ;
	}
	if (init_subcmd(cmd, ast))
		return ;
	cmd->sfd = sfd;
}

int	builtin_inpipes(t_cmd *cmd)
{
	t_builtin	*bt;
	int		status;

	bt = g_sh.builtin;
	while (bt)
	{
		if (!same_strcmp(cmd->cmd[0], bt->name))
		{
			if (redir_cmd(cmd, TRUE))
				exit(EXIT_FAILURE);
			status = bt->f(cmd->cmd);
			dup2(g_sh.fd_bio[0], STDIN_FILENO);
			dup2(g_sh.fd_bio[1], STDOUT_FILENO);
			exit(status);
		}
		bt = bt->next;
	}
	return (FALSE);
}

void	free_exec_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->ncmd)
		free(cmd->cmd[i]);
	free(cmd->cmd);
	free(cmd->sfd);
	cmd->ncmd = 0;
}

t_pipe	*init_sfd(int rd, int wr, int pipe[2], int fd_rd)
{
	t_pipe	*sfd;

	sfd = (t_pipe *)malloc(sizeof(t_pipe));
	sfd->in_out[READ_END] = rd;
	sfd->in_out[WRITE_END] = wr;
	if (rd || wr)
	{
		sfd->fd_pipe[READ_END] = pipe[READ_END];
		sfd->fd_pipe[WRITE_END] = pipe[WRITE_END];
		sfd->fd_rd = fd_rd;
	}
	sfd->redir = NULL;
	return (sfd);
}

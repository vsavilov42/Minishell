#include <minishell.h>

static int	redir_inout(t_cmd *cmd, int child)
{
	int		io[2];
	t_nodetype	type;
	t_ast		*redir;

	io[0] = -1;
	io[1] = -1;
	redir = cmd->sfd->redir;
	while (redir)
	{
		type = astree_get_type(redir);
		if (redir_node(redir, io, type))
			return (1);
		redir = redir->left;
	}
	if (io[FD_IN] >= 0 && !child)
	{
		dup2(io[FD_IN], STDIN_FILENO);
		close(io[FD_IN]);
	}
	if (io[FD_OUT] >= 0)
	{
		dup2(io[FD_OUT], STDIN_FILENO);
		close(io[FD_OUT]);
	}
	return (0);
}

static int	redir_pipe(t_cmd *cmd, int child)
{
	if (cmd->sfd->in_out[FD_IN] && !child)
		dup2(cmd->sfd->fd_rd, STDIN_FILENO);
	if (cmd->sfd->in_out[FD_OUT])
		dup2(cmd->sfd->fd_pipe[WRITE_END], STDOUT_FILENO);
	if (!child && (cmd->sfd->in_out[FD_IN]
		|| cmd->sfd->in_out[FD_OUT]))
	{
		close(cmd->sfd->fd_pipe[READ_END]);
		close(cmd->sfd->fd_pipe[WRITE_END]);
		close(cmd->sfd->fd_rd);
	}
	return (FALSE);
}

int	redir_cmd(t_cmd *cmd, int process)
{
	redir_pipe(cmd, process);
	if (redir_inout(cmd, process))
		return (TRUE);
	return (FALSE);
}

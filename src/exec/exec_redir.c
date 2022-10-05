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
		redir = redir->left;
	}
}

static int	redir_pipe(t_cmd *cmd, int child)
{
	if (cmd->sfd->in_out[FD_IN] && !child)
		dup2(cmd->sfd->fd_rd, STDIN_FILENO);
	if (cmd->sfd->in_out[FD_OUT])
		dup2(cmd->sfd->fd_pipe[WRITE_END], STDOUT_FILENO);
	if (!child && (cmd->sfd->in_out[FD_IN]
		|| cmd->sfd->in_out[FD_OUT]))
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

#include <minishell.h>

static int	redir_node_heredoc(t_ast *redir, int io[2])
{
	if (io[FD_IN] >= 0)
		close(io[FD_IN]);
	io[FD_IN] = open(redir->data, O_RDONLY);
	if (io[FD_IN] == -1)
		return (perror_ret(redir->data, 1));
	if (unlink(redir->data) == -1)
		perror_ret("unlink", -1);
	return (FALSE);	
}

static int	redir_node_infile(t_ast *redir, int io[2])
{
	if (io[FD_IN] >= 0)
		close(io[FD_IN]);
	io[FD_IN] = open(redir->data, O_RDONLY);
	if (io[FD_IN] == -1)
		return (perror_ret(redir->data, 1));
	return (FALSE);	
}

static int	redir_node_append(t_ast *redir, int io[2])
{
	if (io[FD_OUT] >= 0)
		close(io[FD_OUT]);
	io[FD_OUT] = open(redir->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (io[FD_OUT] == -1)
		return (perror_ret(redir->data, 1));
	return (FALSE);
}

static int	redir_node_trunc(t_ast *redir, int io[2])
{
	if (io[FD_OUT] >= 0)
		close(io[FD_OUT]);
	io[FD_OUT] = open(redir->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (io[FD_OUT] == -1)
		return (perror_ret(redir->data, 1));
	return (FALSE);
}

int	redir_node(t_ast *redir, int io[2], t_nodetype type)
{
	if (type & NODE_TRUNC)
	{
		if (redir_node_trunc(redir, io))
			return (TRUE);
	}
	else if (type & NODE_APPEND)
	{
		if (redir_node_append(redir, io))
			return (TRUE);
	}
	else if (type & NODE_RD_IN)
	{
		if (redir_node_infile(redir, io))
			return (TRUE);
	}
	else if (type & NODE_HEREDOC)
	{
		if (redir_node_heredoc(redir, io))
			return (TRUE);
	}
	return (FALSE);
}

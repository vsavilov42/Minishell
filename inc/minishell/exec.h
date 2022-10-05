/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:30:11 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/05 15:57:24 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define EXTERNTMPDIR "/tmp"

# define READ_END 0
# define WRITE_END 1

# define FD_IN 0
# define FD_OUT 1

typedef struct	s_cmd	t_cmd;
typedef struct	s_pipe	t_pipe;

void	print_ast(t_ast *ast, int j);

/* heredoc */

int	exec_heredoc(t_ast *ast);
int	into_heredoc(t_ast *ast);

/* exec */

int	exec_astree(t_ast *ast);
int	exec_cmd(t_ast *ast, t_pipe *sfd);
void	free_exec_cmd(t_cmd *cmd);
int	exec_pipe(t_ast	*ast);
int	into_exec_cmd(t_cmd *cmd);
int	redir_cmd(t_cmd *cmd, int root);

/* utils */

t_pipe	*init_sfd(int rd, int wr, int pipe[2], int fd_rd);
void	init_cmd(t_cmd *cmd, t_pipe *sfd, t_ast *ast);

struct	s_cmd {
	char	**cmd;
	int		ncmd;
	t_pipe	*sfd;
};

struct	s_pipe {
	int	in_out[2];
	int	fd_pipe[2];
	int	fd_rd;
	t_ast	*redir;
};

//exec ->
//check <cmdline> -> <and_or> <--> <cmdline>
//4 types: && || ; <job>
//into <job> -> identify pipe -> : <pipe> ? <child's>
//into <pipe> -> open fd[2] -> : in pipe <cmd> ? <cmd>
//into <cmd> -> <is_builtin> : inpipe ? <child_process>
//into <child_process> -> pid->fork; manage_signals; <manage_zombies> <is_builtin> in pipe;
//into <is_builtin> -> exec builtin / check is in pipes do other funct;
//verify <blanck> -> check cmd is blanck
//if process is TRUE = parent / FALSE = child

//NOTE: <child_process> -> if the parent decides not to wait the child's termination and executes its subsequence task, then the termination of the task do not read the exit status code. This state is known as zombie state.

// heredoc ->
// check <cmdline> -> <and_or> <--> <cmdline>
// into <and_or> -> identify and or / ; sq --> <job>
// into <job> -> identify pipe -> : <pipe> ? <cmd>
// into <pipe> -> handle <cmd> in pipe
// into <cmd> -> add redir name to <hrd> && do <hrd>
// into <hrd> -> create file / int fd to file / flags -> O_RDWR | O_TRUNC | O_CREAT, 0644 / <read>
// NOTE: error in << del << del2 << del3 -> <read> should be in child process
// into <read> -> pid->fork; manage signals; get del to stop reading. swap error status.

#endif

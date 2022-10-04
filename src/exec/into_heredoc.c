#include <minishell.h>

static void	read_heredoc(char *del, int fd)
{
	char	*line;

	line = readline("\033[0;36mShTTyDoc> ");
	while (line)
	{
		if (!same_strcmp(line, del))
		{
			close(fd);
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline("\033[0;36mShTTyDoc> ");
	}
	ft_putstr_fd("Heredoc_error: heredoc finish by del\n", STDERR_FILENO);
	close(fd);
	free(line);
	exit(EXIT_SUCCESS);
}

static int	child_heredoc(char *del, int fd)
{
	pid_t	pid;
	int	s_error;

	pid = fork();
	if (pid < 0)
		return (perror_ret("error: heredoc fork", TRUE));
	if (pid > 0)
	{
		signal_ignore();
		waitpid(pid, &s_error, 0);
		if (WTERMSIG(s_error) + 128 == 130
			&& WIFSIGNALED(s_error))
		{
			return (perror_ret("\n", TRUE));
		}
		manage_signal();
	}
	else
	{
		signal_heredoc();
		read_heredoc(del, fd);
	}
	return (FALSE);
}

int	into_heredoc(t_ast *ast)
{
	int	fd;
	char	*file;

	file = new_file_name(EXTERNTMPDIR);
	if (!file)
		return (perror_ret("error: heredoc file creation.", TRUE));
	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		free(file);
		return (perror_ret(file, TRUE));
	}
	if (child_heredoc(ast->data, fd))
	{
		free(file);
		return (TRUE);
	}
	close(fd);
	free(ast->data);
	ast->data = file;
	return (FALSE);
}

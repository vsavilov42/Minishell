#include <minishell.h>

int	error_command(char **cmd)
{
	char	*tmp;

	tmp = ft_strjoin("ShiTTYsh: command not found: ", *cmd);
	error_msg(tmp);
	write(1, "\n", 1);
	free(tmp);
	return (0);
}

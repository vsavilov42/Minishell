#include <minishell.h>

int	perror_ret(const char *s, int code)
{
	if (!s)
		perror("minishell");
	else
		perror(s);
	return (code);
}

int	error_ret(const char *s, int code)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	return (code);
}

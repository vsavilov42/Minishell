#include <minishell.h>

int	error_ret(const char *s, int code)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	return (code);
}

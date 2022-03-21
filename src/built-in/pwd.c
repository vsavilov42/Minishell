#include <minishell.h>

int	ft_pwd(char **arg)
{
	(void)arg;
	char	*pwd;

	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
		return (0);
	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		free(pwd);
		return (1);
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	return (1);
}

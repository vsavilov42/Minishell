#include <minishell.h>

char	*tmp_from_current(void)
{
	char	*name;
	char	*tmp;

	name = NULL;
	tmp = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
	if (getcwd(tmp, PATH_MAX))
	{
		if (access(tmp, R_OK | W_OK) == 0)
			name = new_file_name(tmp);
		free(tmp);
		if (name)
			return (name);
	}
	return (NULL);
}

char	*tmp_from_home(void)
{
	char	*name;
	char	*tmp;

	name = NULL;
	tmp = return_value("HOME");
	if (tmp)
	{
		if (access(tmp, R_OK | W_OK) == 0)
			name = new_file_name(tmp);
		free(tmp);
		if (name)
			return (name);
		else
			name = tmp_from_current();
	}
	return (name);
}

char	*new_file_name(char *file)
{
	char	*name;
	char	*tmp;
	int	i;

	i = 0;
	while (++i < 100)
	{
		tmp = ft_itoa(i);
		name = ft_strjoin("/.shtty_", tmp);
		free(tmp);
		tmp = name;
		name = ft_strjoin(file, tmp);
		free(tmp);
		if (access(name, F_OK) == -1)
			return (name);
		free(name);
	}
	return (NULL);
}

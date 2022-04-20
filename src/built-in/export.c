#include <minishell.h>

int	ft_export(char **arg)
{
	int	i;

	i = 0;
	if (!same_strcmp(arg[i], "export") && arg[1] == NULL)
		print_lst();
	else
		while (arg[++i])
		{
			if (!bad_str(arg[i]))
			{
				if (!compare_lst(arg[i]))
					replace_environ(arg[i]);
				else
					add_environ(arg[i]);
			}
		}
	return (1);
}

int	contain_equal(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=' && arg[i + 1] == '\0')
			return (0);
	}
	return (1);
}

int	contain_equal_cont(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=' && arg[i + 1])
			return (0);
	}
	return (1);
}

char	*return_value(char *name)
{
	t_envlst	*lst;

	if (!g_sh.env)
		return (NULL);
	lst = g_sh.env;
	while (lst)
	{
		if (!same_strcmp(name, lst->name))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

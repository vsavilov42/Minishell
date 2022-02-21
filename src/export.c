#include <minishell.h>

int	export_env(char **arg)
{
	t_envlst	*lst;
	int	i;

	i = 0;
	lst = g_built.env;
	while (arg[++i])
	{
		if (!contain_equal_cont(arg[i]))
			envlst_add_back(&lst, new_envlst(arg[i]));
		if (!contain_equal(arg[i]))
			envlst_add_back(&lst, new_envlst_equal(arg[i]));
		if (contain_equal_cont(arg[i]) && contain_equal(arg[i]))
			envlst_add_back(&lst, new_envlst_only_name(arg[i]));
	}
	g_built.env = lst;
	if (!ft_strncmp(arg[0], "export", 6) && arg[1] == NULL)
		while (lst)
		{
			printf(" NAME = [%s]\n", lst->name);
			if (lst->value != NULL)
				printf(" VALUE = %s\n", lst->value);
			lst = lst->next;
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

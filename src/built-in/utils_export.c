#include <minishell.h>

void	replace_environ(char *arg)
{
	char		*name;
	t_envlst	*lst;

	lst = g_sh.env;
	name = ft_substr(arg, 0, strlen_env(arg));
	while (lst)
	{
		if (!same_strcmp(lst->name, name))
				lst->value = ft_substr(arg, strlen_env(arg) + 1, ft_strlen(arg));
		lst = lst->next;
	}

}

void	add_environ(char *arg)
{
	t_envlst	*lst;

	lst = g_sh.env;
	if (!contain_equal_cont(arg))
		envlst_add_back(&lst, new_envlst(arg));
	if (!contain_equal(arg))
		envlst_add_back(&lst, new_envlst_equal(arg));
	if (contain_equal_cont(arg) && contain_equal(arg))
		envlst_add_back(&lst, new_envlst_only_name(arg));
	g_sh.env = lst;
}

int	compare_lst(char *arg)
{
	char		*tmp;
	t_envlst	*lst;

	lst = g_sh.env;
	tmp = ft_substr(arg, 0, strlen_env(arg));
	while (lst)
	{
		if (!same_strcmp(lst->name, arg) || !same_strcmp(lst->name, tmp))
		{
			free(tmp);
			return (0);
		}
		lst = lst->next;
	}
	free(tmp);
	return (1);
}

void	print_lst(void)
{
	t_envlst *lst;

	lst = g_sh.env;
	if (lst == NULL)
		return ;
	while (lst)
	{
		ft_putstr_fd(lst->name, 1);
		if (lst->value)
		{
			write(1, "=\"", 2);
			ft_putstr_fd(lst->value, 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		lst = lst->next;
	}
}

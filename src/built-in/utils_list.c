#include <minishell.h>

t_envlst	*new_envlst(char *env)
{
	t_envlst	*lst;

	lst = malloc(sizeof(t_envlst));
	if (lst == NULL)
		return (NULL);
	lst->name = ft_substr(env, 0, strlen_env(env));
	lst->value = ft_substr(env, strlen_env(env) + 1, ft_strlen(env));
	lst->next = NULL;
	return (lst);
}

t_envlst	*new_envlst_only_name(char *env)
{
	t_envlst	*lst;

	lst = malloc(sizeof(t_envlst));
	if (lst == NULL)
		return (NULL);
	lst->name = ft_substr(env, 0, ft_strlen(env));
	lst->value = NULL;
	lst->next = NULL;
	return (lst);
}

t_envlst	*new_envlst_equal(char *env)
{
	t_envlst	*lst;

	lst = malloc(sizeof(t_envlst));
	if (lst == NULL)
		return (NULL);
	lst->name = ft_substr(env, 0, strlen_env(env));
	lst->value = "";
	lst->next = NULL;
	return (lst);
}

void	envlst_add_back(t_envlst **lst, t_envlst *new)
{
	if (!new)
		return ;
	if (*lst)
		envlst_last(*lst)->next = new;
	else
		*lst = new;
}

void	free_lst()
{
	t_bt_lst	*lst;

	lst = g_sh.bt;
	while (lst)
	{
		free(lst->cmd);
		lst = lst->next;
	}
}

t_envlst	*envlst_last(t_envlst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

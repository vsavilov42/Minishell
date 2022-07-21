#include <minishell.h>

void	envlst_clear(t_envlst **lst, void (*del)(void *))
{
	void	*last;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		del((*lst)->name);
		del((*lst)->value);
		last = *lst;
		*lst = (*lst)->next;
		del(last);
	}
	*lst = NULL;
}

void	free_all(void)
{
	envlst_clear(g_sh.env, free);
	free(g_sh.env);
}

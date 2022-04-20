#include <minishell.h>

void	remove_lst(char *name)
{
	t_envlst *last;
	t_envlst *current;
	t_envlst *tmp;

	if (!g_sh.env)
		return ;
	last = g_sh.env;
	if (!same_strcmp(last->name, name))
	{
		tmp = last;
		last = last->next;	
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		g_sh.env = last;
		return ;
	}
	current = last->next;
	while (last && last->next)
	{
		if (!same_strcmp(current->name, name))
		{
			free(current->name);
			free(current->value);
			tmp = last->next;
			if (last->next->next)
				current = last->next->next;
			if (!last->next->next)
				last->next = NULL;
			else
				last->next = current;
			free(tmp);
		}
		if (last->next)
		{
			current = current->next;
			last = last->next;
		}
	}
}

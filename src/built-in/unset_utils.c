/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:44:57 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/21 10:54:50 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	remove_lst_exp(char *n, t_envlst *l, t_envlst *tmp, t_envlst *c);

static int	lst_first_element(t_envlst *lst, char *name)
{
	if (!same_strcmp(lst->name, name))
	{
		free(lst->name);
		free(lst->value);
		*g_sh.env = lst->next;
		free(lst);
		return (1);
	}
	return (0);
}

void	remove_lst(char *name)
{
	t_envlst	*last;
	t_envlst	*current;
	t_envlst	*tmp;

	if (!g_sh.env)
		return ;
	tmp = NULL;
	last = *g_sh.env;
	if (!same_strcmp(name, "PWD") || lst_first_element(last, name))
		return ;
	if (!same_strcmp(last->name, name))
	{
		tmp = last;
		last = last->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		*g_sh.env = (*g_sh.env)->next;
		return ;
	}
	current = last->next;
	remove_lst_exp(name, last, tmp, current);
}

static void	remove_lst_exp(char *n, t_envlst *l, t_envlst *tmp, t_envlst *c)
{
	while (l && l->next)
	{
		if (!same_strcmp(c->name, n))
		{
			free(c->name);
			free(c->value);
			tmp = l->next;
			if (l->next->next)
				c = l->next->next;
			if (!l->next->next)
				l->next = NULL;
			else
				l->next = c;
			free(tmp);
		}
		if (l->next)
		{
			c = c->next;
			l = l->next;
		}
	}
}

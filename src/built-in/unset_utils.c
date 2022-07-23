/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:44:57 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/07/22 20:56:03 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	remove_lst_exp(char *n, t_envlst *l, t_envlst *tmp, t_envlst *c);

void	remove_lst(char *name)
{
	t_envlst	*last;
	t_envlst	*current;
	t_envlst	*tmp;

	if (!g_sh.env)
		return ;
	tmp = NULL;
	last = *g_sh.env;
	if (!same_strcmp(last->name, name))
	{
		tmp = last;
		last = last->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		g_sh.env = &last;
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

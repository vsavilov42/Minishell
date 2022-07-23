/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rvs_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dexposit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:19:06 by dexposit          #+#    #+#             */
/*   Updated: 2022/07/23 16:39:57 by dexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * 	REV_CMD_LINE:
 * 	Esta función devuelve una t_list en la que cada nodo contine un node de nuestra lista de t_cmd pero en el orden inverso al que estaba nuestra lista t_cmd
 * 	Para ello necesitamos
 * 		recorrer t_cmd
 * 			crear el nodo nuevo de t_list que contien t_cmd
 *			añadir el nuevo nodo al final de nuestra t_list
 *		devolver t_list
 */
t_list	*rev_cmd_line(t_cmd *cmd)
{
	t_list	*res;
	t_list	*safe;
	t_cmd	*aux;

	res = ft_lstnew((void *) cmd);
	aux = cmd->next;
	while (aux)
	{
		ft_lstadd_front(&res, ft_lstnew((void *) aux));
		aux = aux->next;
	}
	aux = cmd;
	safe = res;
	while (aux && safe)
	{
		aux->rvs = get_cnt(safe);
		aux = aux->next;
		safe = safe->next;
	}
/*
 * ///IMPRESION
	t_list	*imp;
	imp = res;
	printf("Nuestra lista al revés queda:\n");
	while (imp)
	{
		printf("%s\n",((t_cmd *)imp->content)->argv[1]);
		imp = imp->next;
	}
*/
	free_revlst(res);
	return (res);
}

t_cmd	*get_cnt(t_list *node)
{
	return ((t_cmd *)node->content);
}

void	free_revlst(t_list *lst)
{
	t_list	*aux;
	t_list	*prev;

	aux = lst;
	while (aux)
	{
		prev = aux;
		aux = aux->next;
		free(prev);
	}		
}

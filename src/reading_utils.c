/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:07:53 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/17 12:58:45 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	reading_struct_init(t_reading *vars)
{
	extern char	**environ;

	vars->env = environ;
	vars->tok_status = 0;
	vars->aux_count = 0;
	vars->q_count_aux = 0;
	vars->q_count_aux_2 = 0;
	vars->q_count = 0;
	vars->q_check = 0;
	vars->space_count = 0;
	vars->token = NULL;
	vars->head = NULL;
	vars->temp = NULL;
}

t_token	*last_token(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	token_clear(t_reading *vars)
{
	t_token	*temp;

	vars->token = vars->head;
	if (vars->token == NULL)
		return ;
	while (vars->token)
	{
		free(vars->token->data);
		temp = vars->token;
		vars->token = vars->token->next;
		free(temp);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:07:53 by nortolan          #+#    #+#             */
/*   Updated: 2022/04/28 13:17:24 by nortolan         ###   ########.fr       */
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
	vars->exp_pos = 0;
	vars->quote_type = 0;
	vars->token = NULL;
	vars->head = NULL;
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

	temp = NULL;
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

int	tok_status_check(t_reading *vars, char *line, int i)
{
	if (vars->tok_status == 2 || vars->tok_status == 4)
		vars->tok_status = 0;
	if (vars->tok_status == 0)
	{
		vars->space_count = 0;
		if (vars->q_check == 1)
			vars->q_check = 0;
		vars->q_count_aux_2 = 0;
		vars->count = 0;
	}
	if (vars->tok_status == 5)
	{
		vars->q_count_aux_2 = 0;
		vars->tok_status = 6;
		vars->q_check = 1;
	}
	if ((line[i] == '\0' && vars->tok_status == 1)
		|| (line[i + 1] == '\0' && vars->tok_status == 1
			&& ((line[i] != '\"' && line[i] != '\'') || vars->aux_count > 0)))
	{
		write (2, "Quotation marks not closed\n", 27);
		return (1);
	}
	return (0);
}

int	check_pipes(t_reading *vars)
{
	int	checker;

	checker = 0;
	vars->token = vars->head;
	while (vars->token)
	{
		if (vars->token->type == 2)
		{
			if (checker == 1)
			{
				write (2, "Syntax error near unexpected token `|'\n", 39);
				return (1);
			}
			else
				checker = 1;
		}
		else
			checker = 0;
		vars->token = vars->token->next;
	}
	return (0);
}

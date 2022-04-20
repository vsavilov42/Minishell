/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:06:37 by nortolan          #+#    #+#             */
/*   Updated: 2022/04/05 18:44:00 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quote_destroyer(t_reading *vars, int i, int l)
{
	char	*new_data;
	char	*right_side;
	char	*middle;
	char	*left_side;
	char	*temp;

	new_data = NULL;
	left_side = ft_substr(vars->token->data, 0, i - l);
	middle = ft_substr(vars->token->data, i - l + 1, l - 2);
	right_side = ft_substr(vars->token->data, i,
			ft_strlen(vars->token->data) - i);
	temp = ft_strjoin(left_side, middle);
	new_data = ft_strjoin(temp, right_side);
	free(vars->token->data);
	vars->token->data = ft_strdup(new_data);
	free(new_data);
	free(left_side);
	free(middle);
	free(right_side);
	free(temp);
}

int	remover_status(t_reading *vars, int i, int l)
{
	if (vars->quote_type == 0)
		l = 0;
	if (vars->token->data[i] == '\"' && vars->quote_type == 0
		&& ++l)
		vars->quote_type = 2;
	else if (vars->token->data[i] == '\'' && vars->quote_type == 0
		&& ++l)
		vars->quote_type = 1;
	else if (vars->token->data[i] == '\"' && vars->quote_type == 2
		&& ++l)
		vars->quote_type = 0;
	else if (vars->token->data[i] == '\'' && vars->quote_type == 1
		&& ++l)
		vars->quote_type = 0;
	else
	{
		if (vars->quote_type != 0)
			l++;
	}
	return (l);
}

void	remove_quotes(t_reading *vars)
{
	int	i;
	int	l;

	vars->token = vars->head;
	while (vars->token)
	{
		i = 0;
		vars->quote_type = 0;
		while (vars->token->data[i])
		{
			l = remover_status(vars, i, l);
			i++;
			if (vars->quote_type == 0 && l != 0)
			{
				quote_destroyer(vars, i, l);
				i -= 2;
			}
		}
		vars->token = vars->token->next;
	}
}

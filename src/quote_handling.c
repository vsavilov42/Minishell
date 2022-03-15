/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:17:12 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/15 11:19:09 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_chars(t_reading *vars, char *line, int i)
{
	if (vars->status == 6)
		vars->status = 0;
	while (line[i] != '|' && line[i] != ' ' && line[i] != '\t'
		&& line[i] != '\"' && line[i] != '\'' && line[i])
	{
		vars->count++;
		i++;
	}
	if (vars->status == 3)
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i])
			vars->status = 5;
		else
			vars->status = 4;
	}
	if ((line[i] == '\"' || line[i] == '\'') && vars->status == 0)
	{
		vars->q_count++;
		vars->q_count_aux_2++;
		vars->status = 1;
		vars->count++;
		i++;
	}
	return (i);
}

void	back_quote_check(t_reading *vars, char *line, int i)
{
	if ((line[vars->aux_count] == line[i]) && (vars->q_check == 0
			|| (--vars->q_count_aux <= vars->q_count_aux_2
				&& vars->q_check == 1)))
	{
		vars->status = 2;
		vars->count++;
		vars->aux_count = -2;
	}
	else if (vars->q_count_aux <= vars->q_count_aux_2)
	{
		vars->count++;
		vars->aux_count = -2;
	}
}

int	aux_count_loop(t_reading *vars, char *line, int i)
{
	while ((vars->q_count_aux > vars->q_count_aux_2
			|| (line[vars->aux_count] != '\"'
				&& line[vars->aux_count] != '\'')) && line[vars->aux_count])
	{
		if (line[vars->aux_count] == '\"' || line[vars->aux_count] == '\'')
			vars->q_count_aux--;
		vars->aux_count++;
	}
	if (line[vars->aux_count] == '\"' || line[vars->aux_count] == '\''
		|| vars->q_check == 1)
	{
		back_quote_check(vars, line, i);
		i++;
	}
	return (i);
}

int	quote_handling(t_reading *vars, char *line, int i)
{
	if ((line[i] == '\"' || line[i] == '\'') && vars->status == 1)
	{
		vars->q_count++;
		vars->q_count_aux_2++;
		if (line[i] == line[i - vars->count] && vars->q_check == 0)
		{
			vars->status = 2;
			vars->count++;
		}
		else if ((line[i - vars->count] != '\"'
				&& line[i - vars->count] != '\'') || vars->q_check == 1)
		{
			vars->aux_count = -1;
			vars->q_count_aux = vars->q_count;
			while (++vars->aux_count < i && vars->aux_count >= 0)
				i = aux_count_loop(vars, line, i) - 1;
		}
		else
		{
			vars->count++;
			vars->aux_count = -2;
		}
		i++;
	}
	return (i);
}

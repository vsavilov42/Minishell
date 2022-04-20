/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:22:34 by nortolan          #+#    #+#             */
/*   Updated: 2022/04/05 18:34:05 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: fuera de comillas se lia con el &, el > o <, el ( o ), el \, el ';';
//TODO: $?
//TODO: testear espacios;
//TODO: el value viene sin comillas? -> deberia venir con:
//probar con "     hola     a '""' fdghsdfa'fd' '   'fds" y comparar con bash
//o simplemente export="''" y comparar con bash $a y "$a"

void	remove_spaces(t_reading *vars, char *value)
{
	int		i;
	char	*left_side;
	char	*right_side;

	i = -1;
	value = ft_strtrim(value, " ");
	while (value[++i])
	{
		if (value[i] == ' ' || value[i] == '\t')
			vars->space_count++;
		else
			vars->space_count = 0;
		if (vars->space_count > 1)
		{
			left_side = ft_substr(value, 0, i - 1);
			right_side = ft_substr(value, i, ft_strlen(value) - i);
			free(value);
			value = ft_strjoin(left_side, right_side);
			i--;
			free(left_side);
			free(right_side);
		}
	}
	vars->space_temp = ft_strdup(value);
	free(value);
}

void	change_token(t_reading *vars, char *value, int l)
{
	char	*new_data;
	char	*right_side;
	char	*left_side;
	char	*temp;

	new_data = NULL;
	if (vars->quote_type == 0)
	{
		remove_spaces(vars, value);
		free(value);
		value = ft_strdup(vars->space_temp);
		free(vars->space_temp);
	}
	left_side = ft_substr(vars->token->data, 0, vars->exp_pos);
	right_side = ft_substr(vars->token->data, vars->exp_pos + l + 1,
			ft_strlen(vars->token->data) - (vars->exp_pos + l - 1));
	temp = ft_strjoin(left_side, value);
	new_data = ft_strjoin(temp, right_side);
	free(vars->token->data);
	vars->token->data = ft_strdup(new_data);
	free(new_data);
	free(value);
	free(left_side);
	free(right_side);
	free(temp);
}

void	get_variable(t_reading *vars, int i)
{
	int		l;
	char	*name;
	char	*value;

	l = 0;
	name = NULL;
	while ((vars->token->data[i] >= 65 && vars->token->data[i] <= 90)
		|| (vars->token->data[i] >= 97 && vars->token->data[i] <= 122)
		|| (vars->token->data[i] >= 48 && vars->token->data[i] <= 57))
	{
		l++;
		i++;
	}
	if (l != 0)
	{
		name = ft_substr(vars->token->data, i - l, l);
		if (return_value(name))
			value = ft_strdup(return_value(name));
		else
			value = ft_strdup("");
		change_token(vars, value, l);
		free(name);
	}
}

int	get_quote_type(t_reading *vars, int i)
{
	if (vars->token->data[i] == '\"' && vars->quote_type == 0 && ++i)
		vars->quote_type = 2;
	else if (vars->token->data[i] == '\'' && vars->quote_type == 0 && ++i)
		vars->quote_type = 1;
	else if (vars->token->data[i] == '\"' && vars->quote_type == 2 && ++i)
		vars->quote_type = 0;
	else if (vars->token->data[i] == '\'' && vars->quote_type == 1 && ++i)
		vars->quote_type = 0;
	else if (vars->token->data[i] == '$' && vars->quote_type % 2 == 0)
	{
		vars->exp_pos = i;
		i++;
		get_variable(vars, i);
	}
	else
		i++;
	return (i);
}

void	tok_expand(t_reading *vars)
{
	int	i;

	vars->quote_type = 0;
	vars->token = vars->head;
	while (vars->token)
	{
		i = 0;
		while (vars->token->data[i])
		{
			i = get_quote_type(vars, i);
		}
		vars->token = vars->token->next;
	}
}

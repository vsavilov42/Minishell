/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:06:09 by nortolan          #+#    #+#             */
/*   Updated: 2022/07/22 20:18:08 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <minishell.h>

//TODO: "\""  ?????
//TODO: testear a full;
//TODO: no leaks;

void	normal_token(t_reading *vars, char *line, int i)
{
	t_token	*temp;

	temp = NULL;
	if (vars->tok_status == 2 && line[i] != ' ' && line[i]
		!= '\t' && line[i] != 124 && line[i] != 62 && line[i] != 60 && line[i])
		vars->tok_status = 3;
	if (vars->tok_status != 1 && vars->tok_status != 3 && vars->tok_status != 5)
	{
		if (vars->token)
		{
			vars->token = last_token(vars->token);
			temp = vars->token;
			vars->token = vars->token->next;
		}
		vars->token = malloc(sizeof(t_token));
		if (vars->token == NULL)
			exit (1);
		if (temp)
			temp->next = vars->token;
		if (i - vars->count - vars->space_count == 0)
			vars->head = vars->token;
		vars->token->data = ft_substr(line, i - vars->count, vars->count);
		vars->token->type = 1;
		vars->token->next = NULL;
	}
}

int	token_type(t_reading *vars, char *line, int i, int check)
{
	if (i - vars->space_count == 0)
		vars->head = vars->token;
	if ((line[i] == '>' && line[i + 1] == '>')
		|| (line[i] == '<' && line[i + 1] == '<'))
	{
		vars->token->data = ft_substr(line, i, 2);
		check = 1;
	}
	else
		vars->token->data = ft_substr(line, i, 1);
	if (line[i] == '|')
		vars->token->type = 2;
	if (line[i] == '>')
	{
		vars->token->type = 3;
		if (line[i] == line[i + 1])
			vars->token->type = 5;
	}
	if (line[i] == '<')
	{
		vars->token->type = 4;
		if (line[i] == line[i + 1])
			vars->token->type = 6;
	}
	return (check);
}

int	other_token(t_reading *vars, char *line, int i)
{
	int		check;
	t_token	*temp;

	temp = NULL;
	check = 0;
	if (vars->tok_status != 1)
	{
		if (vars->token)
		{
			vars->token = last_token(vars->token);
			temp = vars->token;
			vars->token = vars->token->next;
		}
		vars->token = malloc(sizeof(t_token));
		if (vars->token == NULL)
			exit (1);
		if (temp)
			temp->next = vars->token;
		check = token_type(vars, line, i, check);
		vars->token->next = NULL;
		vars->token = vars->token->next;
	}
	else
		vars->count++;
	return (check);
}

//TODO: test >>>  a ver que hace;
//TOKEN TYPES: normal = 1; pipe = 2; > = 3, < = 4; >> = 5; << = 6;
int	line_handler(t_reading *vars, char *line, int i)
{
	if (i == 0)
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		vars->space_count = i;
	}
	vars->token = vars->head;
	if ((line[i] != '|' && line[i] != '<' && line[i] != '>')
		|| vars->tok_status == 6)
	{
		i = skip_chars(vars, line, i);
		i = quote_handling(vars, line, i);
		normal_token(vars, line, i);
	}
	else
	{
		if (other_token(vars, line, i++))
			i++;
	}
	while (line[i] == ' ' || line[i] == '\t')
	{
		vars->count++;
		i++;
	}
	return (i);
}

void	get_lines(char *line)
{
	int			i;
	int			break_check;
	t_reading	vars;

	i = 0;
	break_check = 0;
	reading_struct_init(&vars);
	while (line[i] || vars.tok_status == 1)
	{
		if (tok_status_check(&vars, line, i))
		{
			break_check = 1;
			break ;
		}
		i = line_handler(&vars, line, i);
	}
	break_check = check_pipes(&vars);
	if (!break_check)
	{
		tok_expand(&vars);
		parse(&vars);
	}
	token_clear(&vars);
}

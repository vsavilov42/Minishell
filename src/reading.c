/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:06:09 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/15 11:23:51 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <minishell.h>

//TODO: testear a full;
//TODO: no leaks;

int	status_check(t_reading *vars, char *line, int i)
{
	if (vars->status == 2 || vars->status == 4)
		vars->status = 0;
	if (vars->status == 0)
	{
		vars->space_count = 0;
		if (vars->q_check == 1)
			vars->q_check = 0;
		vars->q_count_aux_2 = 0;
		vars->count = 0;
	}
	if (vars->status == 5)
	{
		vars->q_count_aux_2 = 0;
		vars->status = 6;
		vars->q_check = 1;
	}
	if ((line[i] == '\0' && vars->status == 1)
		|| (line[i + 1] == '\0' && vars->status == 1
			&& ((line[i] != '\"' && line[i] != '\'') || vars->aux_count > 0)))
	{
		write (2, "Quotation marks not closed\n", 27);
		return (1);
	}
	return (0);
}

void	normal_token(t_reading *vars, char *line, int i)
{
	if (vars->status == 2 && line[i] != ' ' && line[i]
		!= '\t' && line[i] != '|' && line[i])
		vars->status = 3;
	if (vars->status != 1 && vars->status != 3 && vars->status != 5)
	{
		if (vars->token)
		{
			vars->token = last_token(vars->token);
			vars->temp = vars->token;
			vars->token = vars->token->next;
		}
		vars->token = malloc(sizeof(t_token));
		if (vars->token == NULL)
			exit (1);
		if (vars->temp)
			vars->temp->next = vars->token;
		if (i - vars->count - vars->space_count == 0)
			vars->head = vars->token;
		vars->token->data = ft_substr(line, i - vars->count, vars->count);
		vars->token->type = 1;
		vars->token->next = NULL;
	}
}

int	pipe_token(t_reading *vars, char *line, int i)
{
	if (vars->status != 1)
	{
		if (vars->token)
		{
			vars->token = last_token(vars->token);
			vars->temp = vars->token;
			vars->token = vars->token->next;
		}
		vars->token = malloc(sizeof(t_token));
		if (vars->token == NULL)
			exit (1);
		if (vars->temp)
			vars->temp->next = vars->token;
		if (i - vars->space_count == 0)
			vars->head = vars->token;
		vars->token->data = ft_substr(line, i, 1);
		vars->token->type = 2;
		vars->token->next = NULL;
		vars->token = vars->token->next;
	}
	else
		vars->count++;
	i++;
	return (i);
}

int	line_handler(t_reading *vars, char *line, int i)
{
	if (i == 0)
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		vars->space_count = i;
	}
	vars->token = vars->head;
	if (line[i] != '|' || vars->status == 6)
	{
		i = skip_chars(vars, line, i);
		i = quote_handling(vars, line, i);
		normal_token(vars, line, i);
	}
	else
		i = pipe_token(vars, line, i);
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
	t_reading	vars;

	i = 0;
	reading_struct_init(&vars);
	while (line[i] || vars.status == 1)
	{
		if (status_check(&vars, line, i))
			break ;
		i = line_handler(&vars, line, i);
	}
	token_clear(&vars);
}

/*while (vars.head)
{
	printf("head test: %s\n", vars.head->data);
	vars.head = vars.head->next;
}*/

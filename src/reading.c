/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:06:09 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/10 21:34:14 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <minishell.h>

//TODO: head no funciona si hay un espacio al principio;
//TODO: variable prev que apunte al next;
//TODO: testear a full;
//TODO: mirar leaks;
//TODO: leaks de head?;

void	reading_struct_init(t_reading *vars)
{
	vars->status = 0;
	vars->aux_count = 0;
	vars->q_count_aux = 0;
	vars->q_count_aux_2 = 0;
	vars->q_count = 0;
	vars->q_check = 0;
	vars->token = NULL;
	vars->head = NULL;
	vars->temp = NULL;
}

int	status_check(t_reading *vars, char *line, int i)
{
	if (vars->status == 2 || vars->status == 4)
		vars->status = 0;
	if (vars->status == 0)
	{
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

t_token	*last_token(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	//printf("hola?\n");
	while (lst->next)
	{
		printf("data en bucle: %s\n", lst->data);
		lst = lst->next;
	}
	return (lst);
}

void	normal_token(t_reading *vars, char *line, int i)
{
	if (vars->status == 2 && line[i] != ' ' && line[i]
		!= '\t' && line[i] != '|' && line[i])
		vars->status = 3;
	if (vars->status != 1 && vars->status != 3 && vars->status != 5)
	{
		//printf("testeoo: %d\n", i - vars->count);
		//printf("testeoo address: %p\n", vars->token);
		//printf("testeoo head address: %p\n", vars->head);
		//vars->head = vars->token;
		if (vars->token)
		{
			vars->token = last_token(vars->token);
			vars->temp = vars->token;
			printf("teeeeeemp: %s\n", vars->temp->data);
			vars->token = vars->token->next;
		}
		vars->token = malloc(sizeof(t_token));
		if (vars->token == NULL)
			exit (1);
		if (vars->temp)
		{
			vars->temp->next = vars->token;
		}
		if (i - vars->count == 0) //????
		{
			vars->head = vars->token;
		}
		vars->token->data = ft_substr(line, i - vars->count, vars->count);
		vars->token->type = 1;
		vars->token->next = NULL;
		//if (i - vars->count == 0
		//	|| (vars->status == 2 && i - vars->count - 2 == 0))
		//{
		//}
		printf("token: %s\n", vars->token->data);
		printf("type: %d\n\n", vars->token->type);
		//printf("address: %p\n\n", vars->token->data);
		//free(vars->token); //? deberia tener que hacerse al final
	}
	//if (vars->head)
	//	return (vars->head);
	//return (vars->token);
}

int	pipe_token(t_reading *vars, char *line, int i)
{
	if (vars->status != 1)
	{
		if (vars->token)
		{
			vars->token = last_token(vars->token);
			vars->temp = vars->token;
			printf("teeeeeemp: %s\n", vars->temp->data);
			vars->token = vars->token->next;
		}
		vars->token = malloc(sizeof(t_token));
		if (vars->token == NULL)
			exit (1);
		if (vars->temp)
		{
			printf("!!!!!!!!!!!!!!\n");
			vars->temp->next = vars->token;
		}
		if (i == 0)
		{
			vars->head = vars->token;
		}
		vars->token->data = ft_substr(line, i, 1);
		vars->token->type = 2;
		vars->token->next = NULL;
		printf("token: %s\n", vars->token->data);
		printf("type: %d\n\n", vars->token->type);
		//printf("address: %p\n\n", vars->token->data);
		//free(vars->token); //? deberia tener que hacerse al final;
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
	}
	vars->token = vars->head;
	if (line[i] != '|' || vars->status == 6)
	{
		i = skip_chars(vars, line, i);
		i = quote_handling(vars, line, i);
		normal_token(vars, line, i);
	}
	else
	{
		i = pipe_token(vars, line, i);
	}
	while (line[i] == ' ' || line[i] == '\t')
	{
		vars->count++;
		i++;
	}
	return (i);
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
		//free(vars->token->type);
		temp = vars->token;
		vars->token = vars->token->next;
		free(temp);
	}
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
	//token_clear(&vars);
	//vars.token = vars.head;//DESCOMENTAR SI NECESARIO VOLVER A CABEZA DE LISTA
	while (vars.token)
	{
		printf("test: %s\n", vars.token->data);
		printf("test next: %p\n", vars.token->next);
		vars.token = vars.token->next;
	}
	printf("\n");
	while (vars.head)
	{
		printf("head test: %s\n", vars.head->data);
		printf("head test next: %p\n", vars.head->next);
		vars.head = vars.head->next;
	}
	printf("------------------------------------------------\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:06:09 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/01 16:38:44 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <minishell.h>

//TODO: testear a full;
//TODO: mirar leaks;

void	reading_struct_init(t_reading *vars)
{
	vars->status = 0;
	vars->aux_count = 0;
	vars->q_count_aux = 0;
	vars->q_count_aux_2 = 0;
	vars->q_count = 0;
	vars->q_check = 0;
}

void	get_lines(char *line)
{
	int			i;
	t_reading	*vars;
	t_token		*token;
	t_token		*head;

	i = 0;

	vars = malloc(sizeof(t_reading));
	if (vars == NULL)
		exit (1);
	reading_struct_init(vars);
	while (line[i] || vars->status == 1)
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
		if ((line[i] == '\0' && vars->status == 1) || (line[i + 1] == '\0' && vars->status == 1 && ((line[i] != '\"' && line[i] != '\'') || vars->aux_count > 0)))
		{
			write (2, "Quotation marks not closed\n", 27);
			break;
		}
		if (i == 0)
		{
			while (line[i] == ' ' || line[i] == '\t')
				i++;
		}
		if (line[i] != '|' || vars->status == 6)
		{
			if (vars->status == 6)
				vars->status = 0;
			while (line[i] != '|' && line[i] != ' ' && line[i] != '\t' && line[i] != '\"' && line[i] != '\'' && line[i])
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
			if ((line[i] == '\"' || line[i] == '\'') && vars->status == 1)
			{
				vars->q_count++;
				vars->q_count_aux_2++;
				if (line[i] == line[i - vars->count] && vars->q_check == 0)
				{
					vars->status = 2;
					i++;
					vars->count++;
				}
				//TODO: cambiar esto por un else if;
				else if ((line[i - vars->count] != '\"' && line[i - vars->count] != '\'') || vars->q_check == 1)
				{
					vars->aux_count = -1;
					vars->q_count_aux = vars->q_count;
					while (++vars->aux_count < i && vars->aux_count >= 0)
					{
						while ((vars->q_count_aux > vars->q_count_aux_2 || (line[vars->aux_count] != '\"' && line[vars->aux_count] != '\'')) && line[vars->aux_count])
						{
							if (line[vars->aux_count] == '\"' || line[vars->aux_count] == '\'')
								vars->q_count_aux--;
							vars->aux_count++;
						}
						if (line[vars->aux_count] == '\"' || line[vars->aux_count] == '\'' || vars->q_check == 1)
						{
							vars->q_count_aux--;
							if ((line[vars->aux_count] == line[i]) && (vars->q_check == 0 || (vars->q_count_aux <= vars->q_count_aux_2 && vars->q_check == 1)))
							{
								vars->status = 2;
								i++;
								vars->count++;
								vars->aux_count = -2;
							}
							else if (vars->q_count_aux <= vars->q_count_aux_2) // <= 2 ??
							{
								i++;
								vars->count++;
								vars->aux_count = -2;
							}
						}
					}
					if (vars->aux_count != -1)
					{
						i++;
						vars->count++;
					}
				}
				else
				{
					i++;
					vars->count++;
					vars->aux_count = -2;
				}

			}
			if (vars->status == 2 && line[i] != ' ' && line[i] != '\t' && line[i] != '|' && line[i])
			{
				vars->status = 3;
			}
			if (vars->status != 1 && vars->status != 3 && vars->status != 5)
			{
				token = malloc(sizeof(t_token));
				if (token == NULL)
					exit (1);
				token->data = ft_substr(line, i - vars->count, vars->count);
				token->type = 1;
				token->next = NULL;
				if (i - vars->count == 0 || (vars->status == 2 && i - vars->count - 2 == 0))
				{
					head = token;
					write(1, "TEST\n", 5);
				}
				printf("token: %s\n", token->data);
				printf("type: %d\n\n", token->type);
				token = token->next;
			}
		}
		else
		{
			if (vars->status != 1)
			{
				token = malloc(sizeof(t_token));
				if (token == NULL)
					exit (1);
				token->data = ft_substr(line, i, 1);
				token->type = 2;
				token->next = NULL;
				printf("token: %s\n", token->data);
				printf("type: %d\n\n", token->type);
				if (i == 0)
					head = token;
				token = token->next;
			}
			else
				vars->count++;
			i++;
		}
		while (line[i] == ' ' || line[i] == '\t')
		{
			vars->count++;
			i++;
		}
		/*if (status != 1) //PARA TEST/////////////////////////
		  {
		  printf("head token: %s\n", head->data);
		  printf("head type: %d\n\n", head->type);
		  }*/
	}
}

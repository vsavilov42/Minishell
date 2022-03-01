/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:06:09 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/01 14:00:40 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <minishell.h>

//TODO: testear a full;
//TODO: mirar leaks;

void	get_lines(char *line)
{
	int		i;
	int		status;
	int		count;
	int		aux_count;
	int		q_count;
	int		q_count_aux;
	int		q_count_aux_2;
	int		q_check;
	t_token	*token;
	t_token	*head;

	i = 0;
	status = 0;
	aux_count = 0;
	q_count_aux = 0;
	q_count_aux_2 = 0;
	q_count = 0;
	q_check = 0;
	while (line[i] || status == 1)
	{
		if (status == 2 || status == 4)
			status = 0;
		if (status == 0)
		{
			if (q_check == 1)
				q_check = 0;
			q_count_aux_2 = 0;
			count = 0;
		}
		if (status == 5)
		{
			q_count_aux_2 = 0;
			status = 6;
			q_check = 1;
		}
		if ((line[i] == '\0' && status == 1) || (line[i + 1] == '\0' && status == 1 && ((line[i] != '\"' && line[i] != '\'') || aux_count > 0)))
		{
			write (2, "Quotation marks not closed\n", 27);
			break;
		}
		if (i == 0)
		{
			while (line[i] == ' ' || line[i] == '\t')
				i++;
		}
		if (line[i] != '|' || status == 6)
		{
			if (status == 6)
				status = 0;
			while (line[i] != '|' && line[i] != ' ' && line[i] != '\t' && line[i] != '\"' && line[i] != '\'' && line[i])
			{
				count++;
				i++;
			}
			if (status == 3)
			{
				if (line[i] != ' ' && line[i] != '\t' && line[i])
					status = 5;
				else
					status = 4;
			}
			if ((line[i] == '\"' || line[i] == '\'') && status == 0)
			{
				q_count++;
				q_count_aux_2++;
				status = 1;
				count++;
				i++;
			}
			if ((line[i] == '\"' || line[i] == '\'') && status == 1)
			{
				q_count++;
				q_count_aux_2++;
				if (line[i] == line[i - count] && q_check == 0/* ||(line[i - count - 1] != '\"' && line[i - count - 1] != '\'')*/)
				{
					status = 2;
					i++;
					count++;
				}
				else
				{
					//TODO: cambiar esto por un else if;
					if ((line[i - count] != '\"' && line[i - count] != '\'') || q_check == 1)
					{
						aux_count = -1;
						q_count_aux = q_count;
						while (++aux_count < i && aux_count >= 0)
						{
							while ((q_count_aux > q_count_aux_2 || (line[aux_count] != '\"' && line[aux_count] != '\'')) && line[aux_count])
							{
								if (line[aux_count] == '\"' || line[aux_count] == '\'')
									q_count_aux--;
								aux_count++;
							}
							if (line[aux_count] == '\"' || line[aux_count] == '\'' || q_check == 1)
							{
								q_count_aux--;
								if ((line[aux_count] == line[i]) && (q_check == 0 || (q_count_aux <= q_count_aux_2 && q_check == 1)))
								{
									status = 2;
									i++;
									count++;
									aux_count = -2;
								}
								else if (q_count_aux <= q_count_aux_2) // <= 2 ??
								{
									i++;
									count++;
									aux_count = -2;
								}
							}
						}
						if (aux_count != -1)
						{
							i++;
							count++;
						}
					}
					else
					{
						i++;
						count++;
						aux_count = -2;
					}
				}
			}
			if (status == 2 && line[i] != ' ' && line[i] != '\t' && line[i] != '|' && line[i])
			{
				status = 3;
			}
			if (status != 1 && status != 3 && status != 5)
			{
				token = malloc(sizeof(t_token));
				if (token == NULL)
					exit (1);
				token->data = ft_substr(line, i - count, count);
				token->type = 1;
				token->next = NULL;
				if (i - count == 0 || (status == 2 && i - count - 2 == 0))
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
			if (status != 1)
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
				count++;
			i++;
		}
		while (line[i] == ' ' || line[i] == '\t')
		{
			count++;
			i++;
		}
		/*if (status != 1) //PARA TEST/////////////////////////
		{
			printf("head token: %s\n", head->data);
			printf("head type: %d\n\n", head->type);
		}*/
	}
}

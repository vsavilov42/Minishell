/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:06:09 by nortolan          #+#    #+#             */
/*   Updated: 2022/02/18 18:03:53 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: test fallido: tabulaciones;
//TODO: test fallido: a"b'c'd"e
//TODO: test fallido: "b'c'd"e
//TODO: testear a full;
//TODO: mirar leaks;

void	get_lines(char *line)
{
	int		i;
	int		status;
	int		count;
	int		aux_count;
	t_token	*token;
	t_token	*head;

	i = 0;
	status = 0;
	aux_count = 0;
	while (line[i] || status == 1)
	{
		if (status == 2 || status == 4)
			status = 0;
		if (status == 0)
			count = 0;
		if (line[i + 1] == '\0' && status == 1 && (line[i] != '\"' && line[i] != '\''))
		{
			write (2, "Quotation marks not closed\n", 27);
			break;
		}
		if (line[i] != '|')
		{
			while (line[i] != '|' && line[i] != ' ' && line[i] != '\"' && line[i] != '\'' && line[i])
			{
				count++;
				i++;
			}
			if (status == 3)
				status = 4;
			if ((line[i] == '\"' || line[i] == '\'') && status == 0)
			{
				status = 1;
				i++;
			}
			if ((line[i] == '\"' || line[i] == '\'') && status == 1)
			{
				//printf("TEST LOCO: estoy en: %c, atras hay: %c\n", line[i], line[i - count - 1]);
				//printf("count:  %d\n", count);
				//printf("i:      %d\n", i);
				//printf("status: %d\n\n", status);
				if (line[i] == line[i - count - 1]/* ||(line[i - count - 1] != '\"' && line[i - count - 1] != '\'')*/)
				{
					status = 4;
					i++;
				}
				else
				{
					//printf("estoy aqui lol\n");
					//TODO: cambiar esto por un else if;
					if (line[i - count - 1] != '\"' && line[i - count - 1] != '\'')
					{
						aux_count = i - count - 1;
						while (++aux_count < i && aux_count >= 0)
						{
							//printf("char: %c\n", line[aux_count]);
							if (line[aux_count] == '\"' || line[aux_count] == '\'')
							{
								if (line[aux_count] == line[i])
								{
									//printf("he entrado aqui\n");
									status = 4;
									//i++;
									aux_count = -2;
								}
								else
									aux_count = -2;
							}
						}
						if (aux_count != -2)
						{
							i++;
							count++;
						}
					}
					else
					{
						i++;
						count++;
					}
					/*printf("ALGO VA MAL\n");
					break ;*/
				}
			}
			//printf("status: %d\n", status);
			if (status == 2 && line[i] != ' ' && line[i] != '|' && line[i])
			{
				status = 3;
			}
			if (status != 1 && status != 3)
			{
				token = malloc(sizeof(t_token));
				if (token == NULL)
					exit (1);
				if (status == 0)
					token->data = ft_substr(line, i - count, count);
				if (status == 2 || status == 4)
					token->data = ft_substr(line, i - count - 2, count + 2);
				if (status == 4)
					token->data = ft_substr(line, i - count - 2, count + 2);
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
		while (line[i] == ' ')
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

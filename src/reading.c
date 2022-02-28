/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:06:09 by nortolan          #+#    #+#             */
/*   Updated: 2022/02/28 14:39:20 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: que cojones:  | "|asdsdfh"| ó  | "|asdsdfh"|
//TODO: test fallido: a"b'c'd"e ""'' a"b'c'd"e ""''
//TODO: usar un segundo q_count_aux que compruebe el numero de comillas al que se tiene que quedar q_count_aux al ir restando;
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
		//printf("char actual:   %c\n", line[i]);
		//printf("q_check: %d\n", q_check);
		//if (i >= 1)
		//	printf("pre char actual:   %c\n", line[i - 1]);
		//printf("status actual: %d\n", status);
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
			status = 6;
			q_check = 1;
		}
		if ((line[i] == '\0' && status == 1) || (line[i + 1] == '\0' && status == 1 && ((line[i] != '\"' && line[i] != '\'') || aux_count > 0)))
		{
			//printf("status: %d\n", status);
			//printf("current char: %c\n", line[i]);
			//printf("prev char:    %c\n", line[i - 1]);
			//printf("klk aux_count: %d\n", aux_count);
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
			//printf("HoLAAAA\n");
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
				//printf("toy aqui inicio: %c\n", line[i]);
				q_count++;
				q_count_aux_2++;
				status = 1;
				count++;
				i++;
			}
			if ((line[i] == '\"' || line[i] == '\'') && status == 1)
			{
				//printf("toy aqui final: %c\n", line[i]);
				//printf("line[i - count]: %c\n", line[i - count]);
				//printf("TEST LOCO: estoy en: %c, atras hay: %c\n", line[i], line[i - count]);
				q_count++;
				q_count_aux_2++;
				//printf("q_count: %d\n", q_count);
				if (line[i] == line[i - count]/* ||(line[i - count - 1] != '\"' && line[i - count - 1] != '\'')*/)
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
						//printf("entro en el else\n");
						aux_count = i - count - 1;
						q_count_aux = q_count;
						while (++aux_count < i && aux_count >= 0)
						{
							while (q_count_aux > q_count_aux_2)
							{
								aux_count--;
								if (line[aux_count] == '\"' || line[aux_count] == '\'')
									q_count_aux--;
							}
							if (line[aux_count] == '\"' || line[aux_count] == '\'')
							{
								q_count_aux--;
								if ((line[aux_count] == line[i]) || (q_count_aux <= q_count_aux_2 && q_check == 1))
								{
									//printf("entro en el if\n");
									//printf("-aux_count:	%d\n", aux_count);
									//printf("-aux char:	%c\n", line[aux_count]);
									//printf("-i:			%d\n", i);
									//printf("-i char:		%c\n", line[i]);
									//printf("-q_count_aux: %d\n", q_count_aux);
									//printf("-q_count_aux_2: %d\n", q_count_aux_2);
									status = 2;
									i++;
									count++;
									//printf("i++\n");
									aux_count = -2;
								}
								else if (q_count_aux <= 2) // <= q_count_aux_2 ??
								{
									//printf("entro otra vez?\n");
									i++;
									count++;
									aux_count = -2;
								}
							}
						}
						//printf("aux_count: %d\n", aux_count);
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
			//printf("pre char:   %c\n", line[i]);
			if (status == 2 && line[i] != ' ' && line[i] != '\t' && line[i] != '|' && line[i])
			{
				status = 3;
			}
			//printf("count:  %d\n", count);
			//printf("i:      %d\n", i);
			//printf("status: %d\n", status);
			//printf("char:   %c\n", line[i]);
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
		//printf("status: %d\n", status);
		//printf("pre char: %c\n", line[i - 1]);
		while (line[i] == ' ' || line[i] == '\t')
		{
			//printf("dentro, status = %d\n", status);
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

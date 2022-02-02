/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:06:09 by nortolan          #+#    #+#             */
/*   Updated: 2022/02/02 13:44:43 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*char	*sep_malloc(int j, int count, char **args) //puesto aqui por falta de lineas
{
	args[j] = malloc(sizeof(char) * count + 1);
	if (args[j] == NULL)
		exit (2);
	return (args[j]);
}

char	**separate_lines(int i, int j, char **args, char *line) //separacion por ;
{
	int	count;
	int	sep_check;

	count = 0;
	while (line[++i])
	{
		sep_check = 0;
		count++;
		if (line[i] == '|')
		{
			args[j] = malloc(sizeof(char) * count + 1);
			if (args[j] == NULL)
				exit (2);
			args[j++] = ft_substr(line, i - count + 1, count);
			count = 0;
			sep_check = 1;
		}
		if (sep_check == 0 && line[i + 1] == '\0')
		{
			args[j] = sep_malloc(j, count, args); //llamada a sep_malloc
			args[j++] = ft_substr(line, i - count + 1, count);
		}
	}
	args[j] = NULL;
	return (args);
}

void	get_lines(char *line) //malloc principal y llamada a separacion por ;
{
	int		i;
	int		j;
	int		count;
	char	**args;

	i = -1;
	j = 0;
	count = 0;
	while (line[++i])
	{
		if (line[i] == '|')
			count++;
	}
	if (line[i - 1] != '|')
		count++;
	args = malloc(sizeof(char *) * (count + 1));
	if (args == NULL)
		exit (2);
	i = -1;
	args = separate_lines(i, j, args, line);
	//////para test/////
	j = -1;
	while (args[++j])
		printf("%s\n", args[j]);
	////////////////////
}*/

//TODO: testear a full;
//TODO: mirar leaks;

void	get_lines(char *line)
{
	int		i;
	int		status;
	int		count;
	t_token	*token;
	t_token	*head;

	i = 0;
	status = 0;
	while (line[i] || status == 1)
	{
		if (status == 2 || status == 4)
			status = 0;
		if (status == 0)
			count = 0;
		if (line[i + 1] == '\0' && status == 1 && line[i] != '\"')
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
				printf("TEST LOCO: estoy en: %c, atras hay: %c\n", line[i], line[i - count - 1]);
				if (line[i] == line[i - count - 1] || (line[i - count - 1] != '\"' && line[i - count - 1] != '\''))
				{
					status = 2;
					i++;
				}
				else //////////////////////TEMPORAL//////////////////////
				{
					//TODO: que hago aqui si se mezclan comillas;
					printf("ALGO VA MAL\n");
					break ;
				}
			}
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
				/*if (status == 4)
					token->data = ft_substr(line, i - count - 2, count + 2);*/
				token->type = 1;
				token->next = NULL;
				if (i - count == 0 || (status == 2 && i - count - 2 == 0))
				{
					head = token;
					write(1, "TEST\n", 5);
				}
				printf("token: %s\n", token->data);
				printf("type: %d\n\n", token->type);
				/*printf("i:     %d\n", i);
				printf("count: %d\n\n", count);
				printf("status:     %d\n", status);
				printf("i - count - 2:     %d\n", i - count - 2);*/
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

		//printf("%d\n", token->type);
		//printf("aux %s\n", head->data);
		//printf("aux %d\n", head->type);

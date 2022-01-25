/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:06:09 by nortolan          #+#    #+#             */
/*   Updated: 2022/01/25 13:54:38 by nortolan         ###   ########.fr       */
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

//TODO: no quitar todavia las comillas al tokenizar, se quitan luego

void	get_lines(char *line)
{
	int		i;
	int		status;
	int		count;
	t_token	*token;
	t_token	*head;

	i = 0;
	status = 0;
	while (line[i])
	{
		if (status == 2)
			status = 0;
		if (status == 0)
			count = 0;
		if (line[i] != '|')
		{
			while (line[i] != '|' && line[i] != ' ' && line[i] != '\"' && line[i] != '\'' && line[i])
			{
				count++;
				i++;
			}
			if (line[i] == '\"' && status == 0)
			{
				status = 1;
				i++;
			}
			if (line[i] == '\"' && status == 1)
			{
				status = 2;
				i++;
			}
			if (status != 1)
			{
				token = malloc(sizeof(t_token));
				if (token == NULL)
					exit (1);
				if (status == 0)
					token->data = ft_substr(line, i - count, count);
				if (status == 2)
					token->data = ft_substr(line, i - count - 2, count + 2);
				token->type = 1;
				token->next = NULL;
				if (i - count == 0)
					head = token;
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
		//TODO: probar si aux tiene bien la referencia si la linea empieza por comillas;
		//printf("head token: %s\n", head->data);
		//printf("head type: %d\n\n", head->type);
	}
}

		//printf("%d\n", token->type);
		//printf("aux %s\n", head->data);
		//printf("aux %d\n", head->type);

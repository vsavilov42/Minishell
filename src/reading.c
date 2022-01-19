/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:06:09 by nortolan          #+#    #+#             */
/*   Updated: 2022/01/19 14:10:58 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*sep_malloc(int j, int count, char **args) //puesto aqui por falta de lineas
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
}

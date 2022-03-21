/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:22:34 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/21 13:53:10 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: la variable pilla todo lo que sean numeros y letras;
//TODO: si va entre comillas, to los caracteres palante;
//TODO: fuera de comillas se lia con el &, el > o <, el ( o ), el \, el ';';
//TODO: si la variable no existe y no estamos en comillas simples, se reemplaza por nada;
//TODO; tests importantes con variables que no existen: "'$aaa'"/"$aa'a'a"/ "$aaa"/'$aaa'
//TODO: un dollar suelto se imprime tal cual

/*char	*return_value(char *name)
{
	t_envlst	*lst;

	if (!g_sh.env)
		return (NULL);
	lst = g_sh.env;
	while (lst)
	{
		if (same_strcmp(name, lst->name))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}*/

void	get_variable(t_reading *vars, int i)
{
	int		l;
	char	*name;
	//char	*value;
	//char	*temp;

	l = 0;
	name = NULL;
	while ((vars->token->data[i] >= 65 && vars->token->data[i] <= 90) || (vars->token->data[i] >= 97 && vars->token->data[i] <= 122) || (vars->token->data[i] >= 48 && vars->token->data[i] <= 57))
	{
		l++;
		printf("CHAR: %c\n", vars->token->data[i]);
		i++;
	}
	printf("length: %d\n", l);
	if (l != 0)
	{
		//name = malloc(sizeof(char) * (l + 1));
		//if (name == NULL)
		//	exit (1);
		//temp = ft_strdup(vars->token->data); //esto hace falta?
		name = ft_substr(vars->token->data, i - l, l);
		//free(temp);
		printf("name: %s\n", name);
		//value = ft_strdup(return_value(name));
		free(name);
	}
	//TODO: tener en cuenta si lenght = 0 porque es un dollar suelto;
	//TODO: malloc aqui al name para copiarlo y conseguir luego el value
}

void	tok_expand(t_reading *vars)
{
	int	i;
	int	quote_type;

	quote_type = 0;
	vars->token = vars->head;
	printf("TEST: %s\n", vars->env[0]);
	while (vars->token)
	{
		printf("\n");
		i = 0;
		while (vars->token->data[i])
		{
			printf("char: %c, qtype: %d, i: %d\n", vars->token->data[i], quote_type, i);
			if (vars->token->data[i] == '\"' && quote_type == 0)
			{
				quote_type = 2;
				printf("---cambio a qtype %d\n", quote_type);
				i++;
			}
			else if (vars->token->data[i] == '\'' && quote_type == 0)
			{
				quote_type = 1;
				printf("---cambio a qtype %d\n", quote_type);
				i++;
			}
			else if (vars->token->data[i] == '\"' && quote_type == 2)
			{
				quote_type = 0;
				printf("---cambio a qtype %d\n", quote_type);
				i++;
			}
			else if (vars->token->data[i] == '\'' && quote_type == 1)
			{
				quote_type = 0;
				printf("---cambio a qtype %d\n", quote_type);
				i++;
			}
			else if (vars->token->data[i] == '$' && quote_type % 2 == 0)
			{
				printf("FUNCIONA\n");
				i++;
				get_variable(vars, i);
			}
			else
				i++;
		}
		vars->token = vars->token->next;
	}
}

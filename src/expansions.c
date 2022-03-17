/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:22:34 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/17 13:22:41 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO: la variable pilla todo lo que sean numeros y letras;
//TODO: si va entre comillas, to los caracteres palante;
//TODO: fuera de comillas se lia con el &, el > o <, el ( o ), el \, el ';';
/*void	get_variable(t_reading *vars, int i)
{

}i*/

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
				//get_variable(vars, i);
			}
			else
				i++;
		}
		vars->token = vars->token->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:44:27 by nortolan          #+#    #+#             */
/*   Updated: 2022/04/20 21:39:28 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_init(t_parse *parse)
{
	parse->wc = 0;
	parse->wc_aux = 0;
	parse->cmds = NULL;
	parse->head_cmd = NULL;
}

t_cmd	*last_cmd(t_cmd *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	free_args(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

void	cmds_clear(t_parse *parse)
{
	t_cmd	*temp;

	temp = NULL;
	parse->cmds = parse->head_cmd;
	if (parse->cmds == NULL)
		return ;
	while (parse->cmds)
	{
		free_args(parse->cmds->argv);
		temp = parse->cmds;
		free(parse->cmds->type_arr);
		parse->cmds = parse->cmds->next;
		free(temp);
	}
}

void	create_cmd(t_reading *vars, t_parse *parse)
{
	int		i;
	t_cmd	*temp_cmd;
	t_token	*temp_token;

	i = -1;
	temp_cmd = NULL;
	temp_token = vars->head;
	if (parse->cmds)
	{
		parse->cmds = last_cmd(parse->cmds);
		temp_cmd = parse->cmds;
		parse->cmds = parse->cmds->next;
	}
	parse->cmds = malloc(sizeof(t_cmd));
	if (parse->cmds == NULL)
		exit (1);
	if (temp_cmd)
		temp_cmd->next = parse->cmds;
	parse->cmds->argv = malloc(sizeof(char *) * (parse->wc + 1));
	if (parse->cmds->argv == NULL)
		exit (1);
	parse->cmds->type_arr = malloc(sizeof(int) * parse->wc);
	if (parse->cmds->type_arr == NULL)
		exit (1);
	if (temp_cmd == NULL)
		parse->head_cmd = parse->cmds;
	while (++i < parse->wc_aux)
	{
		temp_token = temp_token->next;
		if (temp_token->type == 2)
			temp_token = temp_token->next;
	}
	i = -1;
	while (++i < parse->wc)
	{
		parse->cmds->argv[i] = ft_strdup(temp_token->data);
		parse->cmds->type_arr[i] = temp_token->type;
		parse->cmds->pos = 1;
		temp_token = temp_token->next;
	}
	parse->cmds->argv[i] = NULL;
	parse->cmds->next = NULL;
	////////////TESTING//////////////
	i = -1;
	while (++i < parse->wc)
	{
		printf("cmds: %s\n", parse->cmds->argv[i]);
		printf("type: %d\n", parse->cmds->type_arr[i]);
		printf("pos:  %d\n", parse->cmds->pos);
//		printf("cmds: %p\n", parse->cmds->argv[i]);
	}
	printf("cmds: %s\n", parse->cmds->argv[i]);
	printf(">>>>>>>>>>>><<<<<<<<<<<<<\n");
	///////////TESTING//////////////
}

//TODO: añadir los types al array de integers;
void	get_cmd(t_reading *vars, t_parse *parse)
{
	vars->token = vars->head;
	while (vars->token)
	{
		if (vars->token->type == 2 || (vars->token->next == NULL && vars->token->type != 2 && ++parse->wc))
		{
			create_cmd(vars, parse);
			parse->wc_aux += parse->wc;
			parse->wc = -1;
		}
		parse->wc++;
		vars->token = vars->token->next;
	}
	parse->head_cmd->pos = 0;
	if (parse->cmds->pos != 0)
		parse->cmds->pos = 2;
	///////////TESTING////////////////////////////
	parse->cmds = parse->head_cmd;
	while (parse->cmds)
	{
		printf("pos: %d\n", parse->cmds->pos);
		parse->cmds = parse->cmds->next;
	}
	//////////////////////////////////////////////
}

void	parse(t_reading *vars)
{
	t_parse	parse;

	remove_quotes(vars);
	//TEST DESPUES DE COMILLAS////////////////////
	vars->token = vars->head;
	while (vars->token)
	{
		printf("test post comillas: %s\n", vars->token->data);
		printf("type: %d\n", vars->token->type);
		vars->token = vars->token->next;
	}
	printf("---------------------------------\n");
	/////////////////////////////////////////////
	parse_init(&parse);
	get_cmd(vars, &parse);
	cmds_clear(&parse);
}

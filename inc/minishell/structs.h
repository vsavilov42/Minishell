/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:12:34 by nortolan          #+#    #+#             */
/*   Updated: 2022/04/20 21:26:00 by nortolan         ###   ########.fr       */
/*   Updated: 2022/03/17 14:41:17 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

//Coloque aquí su estructura

//commands
typedef struct s_cmd
{
	char			**argv;
	int				*type_arr;
	int				pos;
	struct s_cmd	*next;

}	t_cmd;

typedef struct s_parse
{
	int				wc;
	int				wc_aux;
	struct s_cmd	*cmds;
	struct	s_cmd	*head_cmd;
}	t_parse;

//tokens
typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_reading
{
	int				tok_status;
	int				count;
	int				aux_count;
	int				space_count;
	int				q_count;
	int				q_count_aux;
	int				q_count_aux_2;
	int				q_check;
	int				exp_pos;
	int				quote_type;
	char			*space_temp;
	char			**env;
	struct s_token	*token;
	struct s_token	*head;
}	t_reading;

//built-in
typedef struct s_envlst
{
	char	*name;
	char	*value;
	struct s_envlst *next;
}	t_envlst;

typedef struct s_bt_lst
{
	char	*cmd;
	int	(*f)(char **);
	struct s_bt_lst *next;
}	t_bt_lst;

//global
typedef struct s_sh
{
	int		status;
	t_envlst	*env;
	t_bt_lst	*bt;
}	t_sh;

extern	t_sh	g_sh;

#endif

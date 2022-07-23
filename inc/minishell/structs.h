/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:12:34 by nortolan          #+#    #+#             */
/*   Updated: 2022/07/22 20:25:17 by Vsavilov         ###   ########.fr       */
/*   Updated: 2022/03/17 14:41:17 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

//Coloque aquí su estructura

//commands
typedef struct s_cmd
{
	int				*type_arr;
	int				pos;
	char			**argv;
	char			*cmd_path;
	char			**env;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_parse
{
	int				wc;
	int				wc_aux;
	struct s_cmd	*cmds;
	struct s_cmd	*head_cmd;
}			t_parse;

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
	char			*name;
	char			*value;
	struct s_envlst	*next;
}			t_envlst;

//exec
typedef struct s_exec
{
	int		fd_io[2];
	int		pipe_fd[2];
	pid_t	pid;
}		t_exec;

//global
typedef struct s_sh
{
	int			status;
	char		*line;
	t_envlst	**env;
	t_exec		*exec;
	t_cmd		*cmd;
}			t_sh;

extern t_sh	g_sh;

#endif

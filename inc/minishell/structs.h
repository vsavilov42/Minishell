/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:00:14 by vsavilov          #+#    #+#             */
/*   Updated: 2022/11/14 13:44:48 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "lexer.h"
# include "astree.h"

typedef struct s_builtin	t_builtin;
typedef struct s_envlst		t_envlst;
typedef struct s_sh			t_sh;
extern t_sh					g_sh;

//built-in
struct s_builtin
{
	char		*name;
	int			(*f)(char **);
	t_builtin	*next;
};

struct s_envlst
{
	char			*name;
	char			*value;
	struct s_envlst	*next;
};

//global
struct s_sh
{
	int			status;
	char		*line;
	int			fd_bio[2];
	int			is_exp;
	int			subtok;
	int			child;
	pid_t		gpid;
	t_builtin	*builtin;
	t_envlst	**env;
	t_token		*tok;
	t_token		*last;
	t_lexer		*lex;
	t_ast		**astree;
	t_ast		*command;
};

#endif

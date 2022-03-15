/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:12:34 by nortolan          #+#    #+#             */
/*   Updated: 2022/03/07 14:25:55 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

//Coloque aquí su estructura

//built-in


typedef struct s_envlst
{
	char	*name;
	char	*value;
	struct s_envlst *next;
}	t_envlst;

//tokens
typedef struct s_token
{
	char	*data;
	int		type;
	struct s_token	*next;
}	t_token;

typedef struct s_bt_lst
{
	char	*cmd;
	int	(*f)(char **);
	struct s_bt_lst *next;
}	t_bt_lst;

typedef struct s_built
{
	t_envlst	*env;
	t_bt_lst	*bt;
}	t_built;

extern	t_built	g_built;

#endif

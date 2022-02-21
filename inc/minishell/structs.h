/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:12:34 by nortolan          #+#    #+#             */
/*   Updated: 2022/02/19 17:28:06 by Vsavilov         ###   ########.fr       */
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

typedef struct s_built
{
	t_envlst	*env;
}	t_built;

extern	t_built	g_built;

#endif

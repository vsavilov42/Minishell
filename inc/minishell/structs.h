/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:12:34 by nortolan          #+#    #+#             */
/*   Updated: 2022/08/12 13:38:02 by Vsavilov         ###   ########.fr       */
/*   Updated: 2022/03/17 14:41:17 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

//built-in
typedef struct s_envlst
{
	char			*name;
	char			*value;
	struct s_envlst	*next;
}			t_envlst;

//global
typedef struct s_sh
{
	int			status;
	char		*line;
	int		fd_bio[2];
	t_envlst	**env;
}			t_sh;

extern t_sh	g_sh;

#endif

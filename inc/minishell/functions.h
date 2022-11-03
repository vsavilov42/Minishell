/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:11:19 by nortolan          #+#    #+#             */
/*   Updated: 2022/08/12 14:21:59 by Vsavilov         ###   ########.fr       */
/*   Updated: 2022/03/17 14:55:04 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "structs.h"

/* command_analyze.c */

/*int		is_builtin(char **cmd);
void	command_analyze(t_cmd *cmds);
void	command_exec(t_cmd *cmds);
void	standard_command(char **arg);
void	exec_one_command(t_cmd *cmds);
char	**env_pointer(void);
char	**create_path(t_cmd *cmd);*/

void	get_line(char *line);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:10:23 by nortolan          #+#    #+#             */
/*   Updated: 2022/08/12 18:34:45 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <minishell/structs.h>
# include <minishell/functions.h>
# include <minishell/builtin.h>
# include <minishell/envlst.h>
# include <minishell/utils.h>
# include <minishell/signals.h>
# include <minishell/parser.h>
# include <minishell/lexer.h>
# include <minishell/ast.h>

# define PATH_MAX 4096
# define TRUE 1
# define FALSE 0


#endif

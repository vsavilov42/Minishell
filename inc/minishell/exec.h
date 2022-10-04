/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:30:11 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/04 16:55:57 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define EXTERNTMPDIR "/tmp"

void	print_ast(t_ast *ast, int j);

/* heredoc */

int	exec_heredoc(t_ast *ast);
int	into_heredoc(t_ast *ast);

/* exec */

int	exec_astree(t_ast *ast);

/* utils */

char	*new_file(char	*file);


// heredoc ->
// check <cmdline> -> <and_or> <--> <cmdline>
// into <and_or> -> identify and or / ; sq --> <job>
// into <job> -> identify pipe -> : <pipe> ? <cmd>
// into <pipe> -> handle <cmd> in pipe
// into <cmd> -> add redir name to <hrd> && do <hrd>
// into <hrd> -> create file / int fd to file / flags -> O_RDWR | O_TRUNC | O_CREAT, 0644 / <read>
// NOTE: error in << del << del2 << del3 -> <read> should be in child process
// into <read> -> pid->fork; manage signals; get del to stop reading. swap error status.

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:30:11 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/10/04 13:50:39 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void	print_ast(t_ast *ast, int j);

int	exec_heredoc(t_ast *ast);
int	exec_astree(t_ast *ast);

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

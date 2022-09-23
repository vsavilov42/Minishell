/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:32:24 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/09/23 13:29:07 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

typedef struct s_ast	t_ast;
typedef enum e_nodetype	t_nodetype;

// '|' '\' '>' '<' '<<'

enum e_nodetype{
	NODE_PIPE =	(1 << 0),
	NODE_SEQ =	(1 << 1),
	NODE_REDIR =	(1 << 2),
	NODE_RD_IN =	(1 << 3),
	NODE_HEREDOC =	(1 << 4),
	NODE_TRUNC =	(1 << 5),
	NODE_APPEND =	(1 << 6),
	NODE_CMD =	(1 << 7),
	NODE_ARG =	(1 << 8),
	NODE_DATA =	(1 << 9)
};

struct s_ast {
	int				type;
	char			*data;
	struct t_ast	*left;
	struct t_ast	*right;
};

/* ASTREE core */

//ASTreeBinBranch
//ASTreeSetType
//ASTreeSetData
//ASTreeDelNode

/* ---------- */

//Create cmdline (test all command line production)
//cmdline1 <and/or> ; cmdline
//cmdline2 <and/or> ;
//cmdline3 <and/or & cmdline
//cmdline4 <and/or> &
//cmdline5 <and/or>

//Create <and/or>
//and_or1 <job> && <and/or>
//and_or2 <job> || <and/or>
//and_or3 <job>
//and_or4 (<cmdline>) && <and/or>
//and_or5 (<cmdline>) || <and/or>
//and_or6 (<cmdline>)

//Create job (test all jobs) implementing "()"
//job1 (<cmd>) | <job>
//job2 <cmd> | <job>
//job3 (<cmd>)
//job4 <cmd>

//Create cmd (test cmd)
//cmd1 <simple cmd> < <filename>
//cmd2 <simple cmd> > <filename>
//cmd3 <simple cmd>

//Create <simple cmd>
//simplecmd1 = pathname + <tok_lst>

//Create <redir>
//redir1 <redir-in>
//redir2 <redir-out>

//Create <redir-in>
//redirIn1 << + <filename>
//redirIn2 < + <filename>

//Create <tok_lst>
//tokenlist1 <data> + tok_lst
//tokenlist2 <redir> + tok_lst
//tokenlist3 <token> + tok_lst
//tokenlist4 <EMPTY>

void	create_tree(t_ast **ast, t_lexer *lex);



#endif

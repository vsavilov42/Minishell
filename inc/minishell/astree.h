/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:32:24 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/09/22 14:40:00 by Vsavilov         ###   ########.fr       */
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

#endif

#include <minishell.h>

void	command_analyze(t_cmd *cmds)
{
	command_exec(cmds);
}

void	command_exec(t_cmd *cmds)
{
	t_cmd *tmp;

	tmp = cmds;
	while (tmp)
	{
		builtin(tmp->argv);
		tmp = tmp->next;
	}
}

// | exec the last command without saving fd
// > redirect output command, create new one if doesn't exist. if exist, rm and create.
// >> creates the file if doesn't exist. if exist add the content.
// < redirect input command
// << heredoc

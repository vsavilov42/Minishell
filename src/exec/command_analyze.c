#include <minishell.h>

void	command_analyze(t_cmd *cmds)
{
	builtin(cmds->argv);
}

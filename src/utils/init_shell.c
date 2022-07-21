#include <minishell.h>

void	init_minishell(void)
{
	get_env();
	manage_signal();
}

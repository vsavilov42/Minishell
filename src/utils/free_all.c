#include <minishell.h>

void	free_all(void)
{
	envlst_clear(g_sh.env, free);
	free(g_sh.line);
	free(g_sh.exec);
	free_split(g_sh.cmd->argv);
	free(g_sh.cmd->type_arr);
	free(g_sh.cmd);
	free(g_sh.env);
}

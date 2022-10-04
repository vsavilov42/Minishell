#include <minishell.h>

char	*new_file(void)
{
	char	*file;

	file = NULL;
	if (access(EXTERNTMPDIR, R_OK | W_OK) == 0)
	{
		file = new_file_name();
		if (file)
			return (file);
	}
	return (tmp_from_home());
}

#include <minishell.h>

static void start_env(char *shell_lvl, char *pwd);
static void	update_shlvl();
static char	*ft_cplusic(char *num);

void	init_minishell(void)
{
	get_env();
	manage_signal();
}

static char	*ft_cplusic(char *num)
{
	int	i;
	int	n;
	char	*tmp;

	i = -1;
	if (!num)
		return (NULL);
	while (num[++i])
		if (!ft_isdigit(num[i]))
			return ("1");
	n = ft_atoi(num);
	n += 1;
	tmp = ft_itoa(n);
	return (tmp);
}

static void	update_shlvl()
{
	t_envlst	*lst;

	lst = *g_sh.env;
	while (lst)
	{
		if (!same_strcmp(lst->name, "SHLVL"))
			lst->value = ft_cplusic(lst->value);
		lst = lst->next;
	}
}

void	get_env(void)
{
	extern char	**environ;
	int		i;
	char		*pwd;
	char		*shell_lvl;

	i = -1;
	g_sh.env = (t_envlst **)ft_calloc(1, (sizeof(t_envlst *)));
	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!g_sh.env || !pwd)
		return ;
	shell_lvl = ft_strdup("SHLVL=1");
	if (*environ)
	{
		while (environ[++i])
			envlst_add_back(g_sh.env, new_envlst(environ[i]));
		update_shlvl();
		//update shell_lvl
	}
	else
		start_env(shell_lvl, pwd);
	free(pwd);
	free(shell_lvl);
}

static void start_env(char *shell_lvl, char *pwd)
{
	char	*tmp;

	tmp = NULL;
	if (getcwd(pwd, PATH_MAX))
	{
		tmp = ft_strjoin("PWD=", pwd);
		envlst_add_back(g_sh.env, new_envlst(tmp));
	}
	envlst_add_back(g_sh.env, new_envlst(shell_lvl));
	free(tmp);
}

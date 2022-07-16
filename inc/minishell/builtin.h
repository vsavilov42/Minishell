#ifndef BUILTIN_H
# define BUILTIN_H
# include "structs.h"

int	ft_echo(char **arg);
int	ft_cd(char **arg);
int	ft_pwd(char **arg);
int	ft_export(char **arg);
int	ft_unset(char **arg);
int	ft_env(char **arg);
int	ft_exit(char **arg);

/* echo.c */

int		verify_echo(char *str);
void	write_echo(char **arg, int index, int n);

/* export.c */

int		contain_equal(char *arg);
int		contain_equal_cont(char *arg);
char	*return_value(char *name);

/* utils_export.c */

void	add_environ(char *arg);
void	replace_environ(char *arg);
void	print_lst(void);
int		compare_lst(char *arg);

/* utils_unset.c */

void	remove_lst(char *name);

/* builtin.c */

void	builtin(char **arg);
void	call_built(char **cmd);
char	**builtin_cmd(void);

#endif

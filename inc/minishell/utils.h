#ifndef UTILS_H
# define UTILS_H

int	error_msg(char *str);
int	same_strcmp(char *str1, char *str2);
char	*strtolow(char *str);
int	strlen_env(char *env);
void	free_split(char **split);
int	bad_str(char *arg);

char	*ft_cplusic(char *num);

#endif

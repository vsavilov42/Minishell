#include <minishell.h>

char	*ft_cplusic(char *num)
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

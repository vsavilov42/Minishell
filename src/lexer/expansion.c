/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vsavilov <Vsavilov@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:42:52 by Vsavilov          #+#    #+#             */
/*   Updated: 2022/11/14 13:36:54 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	change_name(t_expand *exp, t_token *tok)
{
	char	*name;
	size_t	size;

	if (exp->value == NULL)
		exp->value = ft_strdup("");
	size = ft_strlen(tok->name) - ft_strlen(exp->name) + ft_strlen(exp->value);
	size -= (exp->braket * 2);
	name = (char *)ft_calloc(sizeof(char), size);
	if (!name)
		perror_ret("malloc", 1);
	ft_memcpy(name, tok->name, exp->start -1);
	ft_strcat(name, exp->value);
	ft_strcat(name, tok->name + exp->start + ft_strlen(exp->name)
		+ (exp->braket * 2));
	free(exp->name);
	free(tok->name);
	tok->name = name;
}

static int	is_braket(t_expand *exp, t_token *tok)
{
	int	brk;

	brk = 0;
	if (tok->name[exp->end] == TOK_LPBRK)
	{
		exp->end++;
		if (tok->name[exp->end] == TOK_RPBRK)
			return (error_ret("Error: Bad substitution\n", 1));
		brk = 1;
	}
	return (brk);
}

static int	get_name(t_expand *exp, t_token *tok, int *ste)
{
	exp->braket = is_braket(exp, tok);
	while (tok->name[exp->end])
	{
		if (exp->braket && !ft_isalnum(tok->name[exp->end])
			&& tok->name[exp->end] != '_' && tok->name[exp->end] != TOK_RPBRK)
			return (error_ret("Error: Bad substitution\n", 1));
		if (*ste == STE_DFLT)
		{
			if (!ft_isalnum(tok->name[exp->end]) && tok->name[exp->end] != '_')
				break ;
		}
		else if (*ste == STE_DQUOTE)
		{
			if (!ft_isalnum(tok->name[exp->end]) && tok->name[exp->end] != '_')
				break ;
		}
		exp->end++;
	}
	return (0);
}

static void	special_chars(char c, char **name, char **value)
{
	if (c == TOK_QUEST)
	{
		*name = ft_strdup("?");
		*value = ft_itoa(g_sh.status);
	}
	else if (c == '=')
	{
		*name = ft_strdup("");
		*value = ft_strdup("$");
	}
}

int	expansion(t_token *tok, int *start, int ste)
{
	t_expand	exp;

	(*start)++;
	exp = (t_expand){(*start), (*start), 0, NULL, NULL};
	if (tok->name[*start] == TOK_QUEST || tok->name[*start] == '=')
		special_chars(tok->name[*start], &exp.name, &exp.value);
	else
	{
		get_name(&exp, tok, &ste);
		if (exp.braket == 1 && tok->name[exp.end] != TOK_RPBRK)
			return (error_ret("Error: Bad substitution\n", 1));
		exp.name = ft_substr(tok->name, exp.start + exp.braket,
				exp.end - exp.start - exp.braket);
		if (exp.start + exp.braket == exp.end)
			exp.value = ft_strdup("$");
		else
			exp.value = return_value(exp.name);
	}
	*start -= 2;
	if (exp.value != NULL)
		*start += ft_strlen(exp.value);
	change_name(&exp, tok);
	return (0);
}

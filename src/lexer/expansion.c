#include <minishell.h>

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
	return (0);
}

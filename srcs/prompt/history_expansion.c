#include "shell.h"

static int search_history(char *data, char *found, t_history *history)
{
	int i;
	char string[BUFFSIZE];
	int len;

	len = 0;
	i = -1;
	ft_bzero(string, BUFFSIZE);
	ft_bzero(found, BUFFSIZE);
	while (++i < history->len)
	{
		ft_strcpy(string, history->data[history->len - i - 1]);
		if ((len = ft_strlen(string)))
		{
			if (!ft_strncmp(string, data, ft_strlen(data)))
			{
				ft_strcpy(found, string);
				return (1);
			}
		}
	}
	ft_bzero(found, BUFFSIZE);
	return (0);
}

static int word_expansion(char *string, t_cap *tcap, int index)
{
	char exp[BUFFSIZE];
	char result[BUFFSIZE];
	t_history *history;
	int i;

	history = g_shell->history;
	ft_bzero(exp, BUFFSIZE);
	ft_strncpy(exp, string + index + 1, (tcap->char_len - index));
	if (search_history(exp, result, history))
	{
		i = -1;
		while (++i < (int)ft_strlen(exp) + 1)
			ft_delete_back(tcap);
		ft_insert(result, tcap);
		return (1);
	}
	return (0);
}


static int number_expansion(char *string, t_cap *tcap, int index, int rev)
{
	int a;
	char exp[BUFFSIZE];
	t_history *history;
	int i;

	history = g_shell->history;
	a = 0;
	ft_strncpy(exp, string + index + 1 + rev, (tcap->char_len - index - rev));
	a = atoi(exp);
	if (a > 0 && a < history->len)
	{
		i = -1;
		while (++i < (tcap->char_len - index) + 1 + rev)
			ft_delete_back(tcap);
		if (rev)
			ft_insert(history->data[history->len - a], tcap);
		else
			ft_insert(history->data[a - 1], tcap);
		return (1);
	}
	return (0);
}

static int previous_expansion(t_cap *tcap)
{
	t_history *history;

	history = g_shell->history;
	if (history->len)
	{
		ft_delete_back(tcap);
		ft_delete_back(tcap);
		ft_insert(history->data[history->len - 1], tcap);
		return (1);
	}
	return (0);
}

int expansion_history(char *string, t_cap *tcap, int index)
{
	t_history *history;

	history = g_shell->history;
	if (ft_isalpha(string[index + 1]))
		word_expansion(string, tcap, index);
	else if (string[index - 1] == '!')
		previous_expansion(tcap);
	else if (ft_isdigit(string[index + 1]))
		number_expansion(string, tcap, index, 0);
	else if (string[index + 1] == '-')
		if (ft_isdigit(string[index+2]))
			number_expansion(string, tcap, index, 1);
	return (1);
}

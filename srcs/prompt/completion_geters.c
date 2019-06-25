#include "shell.h"

void	get_tilde(char *path, char *final_path)
{
	char env_home[MAX_PATH];
	int i;

	i = -1;
	env_home[0] = 0;
	while (g_shell->env[++i])
		if (!ft_strncmp(g_shell->env[i], "HOME=", 5))
			ft_strcpy(env_home, g_shell->env[i] + 5);
	if (path[0] == '~' && env_home[0])
	{
		ft_strcpy(final_path, env_home);
		ft_strcpy(final_path + ft_strlen(env_home), path + 1);
	}
	else
		ft_strcpy(final_path, path);
}
int		get_argi(t_cap *tc, int position)
{
	int i;
	int argi;

	argi = 0;
	i = 0;
	while (tc->command[i] && i < position)
		if (tc->command[i] && tc->command[i] == ' ')
		{
			while (tc->command[i] && tc->command[i] == ' ')
				i++;
			argi++;
		}
		else
			while (tc->command[i] && tc->command[i] != ' ')
				i++;
	return (argi);
}
void	get_word(t_cap *tc, int position, char *path)
{
	int i;

	i = position - 1;
	ft_bzero(path, MAX_PATH);
	while (ft_isprint(tc->command[i]) &&
			((!ft_isspace(tc->command[i]) && !is_separator(tc->command, i))
				|| tc->command[i - 1] == '\\'))
		i--;
	ft_strncpy(path, tc->command + i + 1, position - 1 - i);
}
void	get_quote(t_ab *autocomp, char *str)
{
	int		i;
	char	copy[MAX_PATH];

	ft_strcpy(copy, str);
	i = 0;
	if (str[0] == '\'' || str[0] == '"' || str[0] == '{' || str[0] == '[' ||
		str[0] == '(')
	{
		i = 1;
		str[0] == '\'' && (autocomp->after[0] = '\'');
		str[0] == '"' && (autocomp->after[0] = '"');
		str[0] == '{' && (autocomp->after[0] = '{');
		str[0] == '[' && (autocomp->after[0] = '[');
		autocomp->after[1] = '\0';
	}
	else
		autocomp->after[0] = '\0';
	ft_bzero(str, MAX_PATH);
	ft_strcpy(str, copy + i);
}

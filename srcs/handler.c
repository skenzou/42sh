/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:39:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/09/21 23:23:52 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**dup_env(char **env)
{
	char	**p;
	int		i;

	i = ft_split_count((const char **)env);
	if (!(p = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		exit(0);
	i = -1;
	while (env[++i])
		if (!(p[i] = ft_strdup(env[i])))
			exit(0);
	p[i] = NULL;
	return (p);
}

int			debug(void)
{
	int fd;

	return (fd = open("log.log", O_RDWR | O_APPEND | O_CREAT, 0666));
}

static inline void	before_read_line(char *buffer, t_cap *tcap)
{
	int		flags;

	flags = fcntl(0, F_GETFL);
	flags &= ~O_NONBLOCK;
	fcntl(0, F_SETFL, flags);
	signal(SIGINT, sigint_handler);
	signal(SIGWINCH, sigwinch_handler);
	ft_bzero(buffer, 4);
	ft_bzero(tcap->command, BUFFSIZE);
	fflush(stdout);
	while (g_shell->dprompt == 0 && (g_shell->dprompt = 1))
		waitabit(0, 80000000);
	print_prompt_prefix();
}

char	*read_line(t_cap *tcap)
{
	char	buffer[4];
	int		ret;

	ret = 0;
	before_read_line(buffer, tcap);
	if (tcap->overflow)
	{
		ft_insert(tcap->carry, tcap);
		ft_bzero(tcap->carry, 2);
		tcap->overflow = 0;
	}
	while ("42sh")
	{
		ft_bzero(buffer, 4);
		tcsetattr(0, TCSADRAIN, g_shell->term);
		read(0, &buffer, 3);
		if ((ret = read_buffer(buffer, tcap)) == -2)
			return (clean_before_return(tcap));
		else if (!ret)
		{
			tcsetattr(0, TCSADRAIN, g_shell->term_backup);
			return (NULL);
		}
	}
}

int	handler(const char *input)
{
	t_list	*redir;
	char	*in;

	// if (!ft_strcmp(input, "history\n"))
	// {
	// 	debug_history(g_shell->history);
	// 	return (1);
	// }
	if (!(in = ft_strdup(input)))
		exit(1); //TODO + free input ??
	in[ft_strlen(in) - 1] = '\0';
 	in = parse_aliases(in, in, in);
	check_inhib(&in);
	if (g_shell->inhib_mod == 2)
	{
		ft_strdel(&in);
		return (1);
	}
	build_lexer(in, &g_shell->lexer);
	ft_strdel(&in);
	if (g_shell->print_flags & PRINT_LEXER)
		print_lexer(g_shell->lexer);
	ft_parse(g_shell->lexer);
	redir = g_shell->redir;
	handle_hdoc(redir);
	if (g_shell->inhib_mod == 2)
		return (1);
	ft_execute_ast(g_shell->ast);
	ft_lstdel(&redir, redir_delone);      // leak possible
	del_ast(&g_shell->ast);
	g_shell->redir = NULL;
	g_shell->lexer = NULL;
	return (1);
}

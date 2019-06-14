/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 19:31:16 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/14 03:47:16 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

t_signal	g_signals[S_SIZE] = {
	{SIGABRT	, S_ABN	, "ABRT"	, "abort"},
	{SIGALRM	, S_TERM, "ALARM"	, "alarm"},
	{SIGBUS		, S_ABN	, "BUSE"	, "bus error"},
	{SIGCHLD	, S_IGN	, "CHILD"	, "done"},
	{SIGCONT	, S_CONT, NULL		, "continued"},
	{SIGFPE		, S_ABN	, "FPE"		, "floating point exception"},
	{SIGHUP		, S_TERM, "HUP"		, "hangup"},
	{SIGILL		, S_ABN	, "ILL"		, "illegal hardware instruction"},
	{SIGINT		, S_STOP, "INT"		, "interrupt"},
	{SIGKILL	, S_TERM, "KILL"	, "killed"},
	{SIGPIPE	, S_TERM, "PIPE"	, "broken pipe"},
	{SIGQUIT	, S_ABN	, "QUIT"	, "quit"},
	{SIGSEGV	, S_ABN	, "SEGV"	, "segmentation fault"},
	{SIGSTOP	, S_STOP, "STOP"	, "suspended (signal)"},
	{SIGTERM	, S_TERM, "TERM"	, "terminated"},
	{SIGTSTP	, S_STOP, "TSTOP"	, "suspended"},
	{SIGTTIN	, S_STOP, "TTIN"	, "suspended (tty input)"},
	{SIGTTOU	, S_STOP, "TTOU"	, "suspended (tty output)"},
	{SIGUSR1	, S_TERM, "USR1"	, "user-defined signal 1"},
	{SIGUSR2	, S_TERM, "USR2"	, "user-defined signal 2"},
	{SIGPROF	, S_TERM, "PROF"	, "profile signal"},
	{SIGSYS		, S_ABN	, "SYS"		, "invalid system call"},
	{SIGTRAP	, S_ABN	, "TRAP"	, "trace trap"},
	{SIGURG		, S_IGN	, "URG"		, ""},
	{SIGVTALRM	, S_TERM, "VTALARM"	, "virtual time alarm"},
	{SIGXCPU	, S_ABN	, "XCPU"	, "cpu limit exceeded"},
	{SIGXFSZ	, S_ABN	, "XFSZ"	, "file size limit exceeded"},
};

void s_child_handler(int status, t_child *node)
{
	int action;
	char *handler;
	char *stat;

	if (s_get_values(status, &action, &handler, &stat))
		return ;
	//ft_printf("debug: err child : %s: %s\n", handler, stat);
	node->status = status;
	if (status == SIGINT)
	{
		kill(node->pid, SIGHUP);
		remove_pid(node);
	}
	else if (action != S_CONT && action != S_STOP)
	{
		display_pid_long(node, 2);
		remove_pid(node);
	}
	else
		display_pid_long(node, 1);
}

int s_get_values(int status, int *action, char **handler, char **stat)
{
	int i;

	i = -1;
	while (++i < S_SIZE)
	{
		if (status == g_signals[i].sig)
		{
			(action) ? *action = g_signals[i].action : 0;
			(handler) ? *handler = g_signals[i].handler : 0;
			(stat) ? *stat = g_signals[i].status : 0;
			return (0);
		}
	}
	return (1);
}

void sigchld_handler()
{
	update_pid_table();
	signal(SIGCHLD, sigchld_handler);
}

void	resetsign(void)
{
	int	x;

	x = -1;
	while (++x < 33)
		signal(x, SIG_DFL);
}

void init_signal(void)
{
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTSTP, sigtstp_dflhandler);
	signal(SIGINT, sigint_handler);
	signal(SIGWINCH, sigwinch_handler);
	signal(SIGCHLD, sigchld_handler);
}

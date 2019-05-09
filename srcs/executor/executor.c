/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:15:41 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/09 02:26:07 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void 		redirect(char **cmd, char *path, char **env, char simple)
{
	pid_t pid;
	int fd;

	if (simple) // redirection simple '>'
		fd = open(path, O_RDWR | O_APPEND | O_CREAT | O_TRUNC, 0666); // ecraser un le contenu de fichier
	else		// double redirection '>>'
		fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0666); // ecrire fin de fichier
	pid = fork();
	signal(SIGINT, sighandler);
	if (pid == 0)
	{
		dup2(fd, 1); // recupere stdout
		// dup2(fd, 2); // recupere stderr
		execve(cmd[0], cmd, env);
		exit(1);
	}
	wait(&pid);
	ft_splitdel(cmd);
}

void 		pipe_cmds(char **cmd1, char **cmd2, char **env)
{
	int fildes[2];
	pid_t pid;

	pipe(fildes);
	pid = fork();
	signal(SIGINT, sigfork);
	if (pid == 0)
	{
		close(fildes[0]);
		dup2(fildes[1], STDOUT_FILENO); /* recupere stdout de ma 1ere commande */
		dup2(fildes[1], STDERR_FILENO); /* recupere stderr de ma 2eme commande */
		execve(cmd1[0], cmd1, env);
		exit(1);
	}
	pid = fork();
	signal(SIGINT, sigfork);
	if (pid == 0)
	{
		close(fildes[1]);
		dup2(fildes[0], STDIN_FILENO); /* recupere la sortie de pipe dans stdin de ma 2 eme commande */
		execve(cmd2[0], cmd2, env);
		exit(1);
	}
	close(fildes[0]);
	close(fildes[1]);
	wait(&pid);
	wait(&pid);
	ft_splitdel(cmd1);
	ft_splitdel(cmd2);
}

void search_pipe(t_ast *root,char *str, char **env)
{
	if (root != NULL)
	{
		search_pipe(root->left,ft_strjoin(str , " - > left"),env);
		if (root->token->op_type == PIPE)
			pipe_cmds(ft_strsplit(root->left->token->content,' '),
					ft_strsplit(root->right->token->content,' '),env);
		search_pipe(root->right,ft_strjoin(str ,"- > right"), env);
	}
	ft_strdel(&str);
}
/*
** Parcours mon token contenant une redirection et recupere la commande de cette
** redirection et met dans len la length de la commande.
** Exemple: ls > test
** renvoie "ls" et met 3 dans len.
*/
static char		*get_cmd_from_redir(char *cmd, int *len, e_op_type *redir)
{
	char c;

	*len = 0;
	while (cmd[*len])
	{
		if (cmd[*len] == '\\')
			*len+=2;
		if ((cmd[*len] == '"' || cmd[*len] == '\'') && (c = cmd[*len]))
		{
			while (cmd[*len] && cmd[*len] != c)
				(*len)++;
			(*len)++;
		}
		if (!ft_strncmp(cmd + *len, ">>", 2) && (*redir = DBL_GREAT_DASH))
			return (ft_strsub(cmd, 0, *len));
		if (!ft_strncmp(cmd + *len, "<<", 2) && (*redir = DBL_LESS_DASH))
			return (ft_strsub(cmd, 0, *len));
		if (cmd[*len] == '>' && (*redir = GREAT))
			return (ft_strsub(cmd, 0, *len));
		if (cmd[*len] == '<' && (*redir = LESS))
			return (ft_strsub(cmd, 0, *len));
		(*len)++;
	}
	return (NULL);
}

void handle_redir(t_ast *root, char **env)
{
	char *cmd;
	char *path;
	int	cmd_len;
	e_op_type redir;

	cmd = get_cmd_from_redir(root->token->content, &cmd_len, &redir);
	// ft_printf("cmd: |%s|\n",cmd);
	path = root->token->content + cmd_len + 2 + (redir == DBL_LESS_DASH || redir == DBL_GREAT_DASH);
	// ft_printf("path: |%s|\n",path);
	redirect(ft_strsplit(cmd, ' '), path, env, redir == GREAT);
	ft_strdel(&cmd);
}

void ft_execute(t_ast *root, char **env)
{
	if (!root)
		return ;
	if (root->left)
		ft_execute(root->left, env);
	if (root->right)
		ft_execute(root->right, env);
	if (root->token->redir)
		handle_redir(root, env);
	// search_pipe(root, ft_strdup("root"),env);
}

// void 	executor(char **argv, char **env)
// {
//
// }

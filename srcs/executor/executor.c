/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:15:41 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/09 06:48:14 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void 		redirect(char **cmd, int fd, char **env)
{
	pid_t pid;

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
// static char		*get_cmd_from_redir(char *cmd, int *len, e_op_type *redir)
// {
// 	char c;
//
// 	*len = 0;
// 	while (cmd[*len])
// 	{
// 		if (cmd[*len] == '\\')
// 			*len+=2;
// 		if ((cmd[*len] == '"' || cmd[*len] == '\'') && (c = cmd[*len]))
// 		{
// 			while (cmd[*len] && cmd[*len] != c)
// 				(*len)++;
// 			(*len)++;
// 		}
// 		if (!ft_strncmp(cmd + *len, ">>", 2) && (*redir = DBL_GREAT_DASH))
// 			return (ft_strsub(cmd, 0, *len));
// 		if (!ft_strncmp(cmd + *len, "<<", 2) && (*redir = DBL_LESS_DASH))
// 			return (ft_strsub(cmd, 0, *len));
// 		if (cmd[*len] == '>' && (*redir = GREAT))
// 			return (ft_strsub(cmd, 0, *len));
// 		if (cmd[*len] == '<' && (*redir = LESS))
// 			return (ft_strsub(cmd, 0, *len));
// 		(*len)++;
// 	}
// 	return (NULL);
// }

static char		*get_next_word(char **start)
{
	char *end;
	int len;

	end = ft_strchr(*start, ' ');
	if (end)
		len = end - *start;
	else
		len = ft_strlen(*start);
	end = *start;
	(*start) += (len - 1);
	return (ft_strsub(end, 0, len));
}

static void		create_redir(t_list **redirs, char *dest, e_op_type redir_type)
{
	t_redir redir;
	t_list *node;

	redir.dest = dest;
	redir.op_type = redir_type;
	node = ft_lstnew((void *)&redir, sizeof(redir));
	if (!node)
		ft_exit("Failed to malloc a node for my redir list");
	ft_lstadd(redirs, node);
}

static e_op_type	get_redir_type(char **str)
{
	if (!ft_strncmp(*str, ">>", 2))
	{
		(*str)+=3;
		return (DBL_GREAT);
	}
	if (!ft_strncmp(*str, "<<", 2))
	{
		(*str)+=3;
		return (DBL_LESS);
	}
	if (**str == '>')
	{
		(*str)+=2;
		return (GREAT);
	}
	if (**str == '<')
	{
		(*str)+=2;
		return (LESS);
	}
	return (OTHER_OP);
}

static void		fill_redir_list(char *cmd, t_list **redirs)
{
	e_op_type optype;
	char c;

	while (*cmd)
	{
		if (*cmd == '\\')
			cmd+=2;
		if ((*cmd == '"' || *cmd == '\'') && (c = *cmd))
		{
			while (*cmd && *cmd != c)
				cmd++;
			cmd++;
		}
		optype = get_redir_type(&cmd);
		if (optype != OTHER_OP)
			create_redir(redirs, get_next_word(&cmd), optype);
		cmd++;
	}
}

int		open_file(t_redir *redir)
{
	int		fd;

	fd = 0;
	if (redir->op_type == GREAT) // redirection simple '>'
		fd = open(redir->dest, O_RDWR | O_CREAT | O_TRUNC, 0666); // ecraser un le contenu de fichier
	else if (redir->op_type == DBL_GREAT)		// double redirection '>>'
		fd = open(redir->dest, O_RDWR | O_APPEND | O_CREAT, 0666); // ecrire fin de fichier
	else if (redir->op_type == LESS) // redirection '<'
		fd = open(redir->dest, O_RDONLY); // lire depuis le fichier
	if (fd == -1)
	{
		if (errno == EACCES)
			ft_putendl_fd("Permission denied", 2);
		else if (errno == ENOENT)
			ft_putendl_fd("No such file or directory", 2);
		else if (errno == EISDIR)
			ft_putendl_fd("Is a directory", 2);
		else
			ft_putendl_fd("open error", 2);
	}
	return (fd);
}

void	handle_redir(t_ast *root, char **env)
{
	// char *cmd;
	// char *path;
	// int	cmd_len;
	// e_op_type redir;
	t_list *redir;
	t_list *temp;
	t_list *del;
	int		fd;
	int stdout;

	redir = NULL;
	(void)env;
	stdout = dup(1);
	// cmd = get_cmd_from_redir(root->token->content, &cmd_len, &redir);
	// // ft_printf("cmd: |%s|\n",cmd);
	// path = root->token->content + cmd_len + 2 + (redir == DBL_LESS_DASH || redir == DBL_GREAT_DASH);
	// ft_printf("path: |%s|\n",path);
	// redirect(ft_strsplit(cmd, ' '), path, env, redir == GREAT);
	// ft_strdel(&cmd);
	fill_redir_list(root->token->content, &redir);
	ft_lstrev(&redir);
	del = redir;
	ft_printf("======================\n");
	temp = redir;
	while (temp)
	{
		print_optype(((t_redir *)temp->content)->op_type);
		ft_printf(" dest: |%s|\n", ((t_redir *)temp->content)->dest);
		temp = temp->next;
	}
	ft_printf("======================\n");
	while (redir)
	{
		fd = open_file(redir->content);
		((t_redir *)redir->content)->fd = fd;
		// if (fd != -1)
		// 	dup2(fd, stdout);
		temp = redir;
		redir = redir->next;
	}
	redirect(ft_strsplit("/bin/ls", ' '), ((t_redir *)temp->content)->fd, env);
	ft_lstdel(&del, redir_delone);
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

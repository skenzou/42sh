/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:15:41 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/14 07:00:17 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void 		ft_fork(char **cmd, char **env)
{
	pid_t pid;

	pid = fork();
	signal(SIGINT, sighandler);
	if (pid == 0)
	{
		// dup2(fd, STDOUT_FILENO); // recupere stdout
		// dup2(fd, 2); // recupere stderr
		execve(cmd[0], cmd, env);
		exit(1);
	}
	wait(&pid);
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
			pipe_cmds(root->left->token->content,
					root->right->token->content, env);
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

// static char		*go_to_next_word(char **start, char separator)
// {
// 	char *temp;
// 	int len;
// 	char c;
//
// 	len = 0;
// 	while ((*start)[len] && (*start)[len] != separator)
// 	{
// 		if ((*start)[len] == '\\')
// 			len+=2;
// 		if (((*start)[len] == '"' || (*start)[len] == '\'') && (c = (*start)[len]))
// 		{
// 			len++;
// 			while ((*start)[len] && (*start)[len] != c)
// 				len++;
// 		}
// 		len++;
// 	}
// 	temp = (*start);
// 	(*start) += (len + ((*start)[len] != 0));
// 	return (ft_strsub(temp, 0, len));
// 	// end = ft_strchr(*start, ' ');
// 	// if (end)
// 	// 	len = end - *start;
// 	// else
// 	// 	len = ft_strlen(*start);
// 	// end = *start;
// 	// (*start) += (len - 1);
// 	// return (ft_strsub(end, 0, len));
// }
//
// static char		*fetch_command(char **start)
// {
// 	char *temp;
// 	int len;
// 	char c;
//
// 	len = 0;
// 	while ((*start)[len])
// 	{
// 		if ((*start)[len] == '\\')
// 			len+=2;
// 		if (((*start)[len] == '"' || (*start)[len] == '\'') && (c = (*start)[len]))
// 		{
// 			len++;
// 			while ((*start)[len] && (*start)[len] != c)
// 				len++;
// 		}
// 		if (!(*start)[len] || !ft_strncmp((*start) + len, ">>", 2) || !ft_strncmp((*start) + len, "<<", 2)
// 			|| (*start)[len] == '>' || (*start)[len] == '<')
// 			break ;
// 		len++;
// 	}
// 	temp = (*start);
// 	(*start) += len;
// 	return (ft_strsub(temp, 0, len));
// }

// static void		create_redir(t_list **redirs, char *dest, e_op_type redir_type)
// {
// 	t_redir redir;
// 	t_list *node;
//
// 	redir.dest = dest;
// 	redir.op_type = redir_type;
// 	node = ft_lstnew((void *)&redir, sizeof(redir));
// 	if (!node)
// 		ft_exit("Failed to malloc a node for my redir list");
// 	ft_lstadd(redirs, node);
// }
//
// static e_op_type	get_redir_type(char **str)
// {
// 	if (!ft_strncmp(*str, ">>", 2))
// 	{
// 		(*str)+=3;
// 		return (DBL_GREAT);
// 	}
// 	if (!ft_strncmp(*str, "<<", 2))
// 	{
// 		(*str)+=3;
// 		return (DBL_LESS);
// 	}
// 	if (**str == '>')
// 	{
// 		(*str)+=2;
// 		return (GREAT);
// 	}
// 	if (**str == '<')
// 	{
// 		(*str)+=2;
// 		return (LESS);
// 	}
// 	return (OTHER_OP);
// }

// static char		*fill_redir_list(char *cmd, t_list **redirs)
// {
// 	e_op_type optype;
// 	// char c;
// 	// int i;
// 	char *ret;
//
// 	while (*cmd)
// 	{
// 		optype = get_redir_type(&cmd);
// 		if (optype != OTHER_OP)
// 			create_redir(redirs, go_to_next_word(&cmd, ' '), optype);
// 		else
// 			ret = fetch_command(&cmd);
// 	}
// 	return (ret);
// }

char	**get_curr_cmd(t_list *redir)
{
	while (redir)
	{
		if (((t_redir *)redir->content)->end_of_leaf)
			return (((t_redir *)redir->content)->dest);
		redir = redir->next;
	}
	return (NULL);
}

int		open_file(t_redir *redir)
{
	int		fd;

	fd = 0;
	if (redir->op_type == GREAT) // redirection simple '>'
		fd = open(redir->dest[0], O_RDWR | O_CREAT | O_TRUNC, 0666); // ecraser un le contenu de fichier
	else if (redir->op_type == DBL_GREAT)		// double redirection '>>'
		fd = open(redir->dest[0], O_RDWR | O_APPEND | O_CREAT, 0666); // ecrire fin de fichier
	else if (redir->op_type == LESS) // redirection '<'
		fd = open(redir->dest[0], O_RDONLY); // lire depuis le fichier
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

int handle_hdoc(t_redir *redir)
{
	char *input;
	int fd;
	char *eof;

	fd = open(HERE_DOC_TMP, O_RDWR | O_CREAT | O_TRUNC, 0666);
	input = NULL;
	eof = ft_strjoin(redir->dest[0], "\n");
	g_shell->tcap->prompt = "heredoc>";
	while ("21sh")
	{
		input = read_line(g_shell->tcap);
		if (!ft_strcmp(input, eof))
			break ;
		write(fd, input, ft_strlen(input));
	}
	g_shell->tcap->prompt = NULL;
	free(eof);
	close(fd);
	fd = open(HERE_DOC_TMP, O_RDONLY);
	return (fd);
}

static void	expand_and_execute(char **args)
{
	int i;
	char *cmd;

	i = -1;
	while(args[++i])
		remove_quote(&args[i]);
	cmd = hash_table(args[0], g_shell->env);
	if (cmd)
	{
		free(args[0]);
		args[0] = cmd;
		ft_fork(args, g_shell->env);
	}
	else
	{
		ft_printf("xD\n");
		ft_splitdel(args);

	}
}

void		print_redir(t_list *redir)
{
	t_redir *red;
	int i;

	ft_printf("===========================REDIR============================\n");
	while (redir)
	{
		red = ((t_redir *)redir->content);
		i = -1;
		print_optype(red->op_type);
		while (red->dest[++i])
			ft_printf(" dest: |%s|\n", red->dest[i]);
		redir = redir->next;
	}
	ft_printf("============================================================\n");
}


static void		handle_redir()
{
	// char *cmd;
	// char *path;
	// int	cmd_len;
	// e_op_type redir;
	// t_list *redir;
	t_list *temp;
	t_list *redir;
	// t_list *del;
	int		fd;
	int stdout;
	int stdin;
	char **cmd;
	int tempfd;
	int i;
	t_redir *red;


	// save STDOUT && STDIN
	stdout = dup(STDOUT_FILENO);
	stdin = dup(STDIN_FILENO);
	// cmd = get_cmd_from_redir(root->token->content, &cmd_len, &redir);
	// // ft_printf("cmd: |%s|\n",cmd);
	// path = root->token->content + cmd_len + 2 + (redir == DBL_LESS_DASH || redir == DBL_GREAT_DASH);
	// ft_printf("path: |%s|\n",path);
	// redirect(ft_strsplit(cmd, ' '), path, env, redir == GREAT);
	// ft_strdel(&cmd);
	// cmd = fill_redir_list(root->token->content, &redir);
	// ft_lstrev(&redir);
	// del = redir;
	redir = g_shell->redir;

	//Apply all redirection
	while (redir && ((t_redir *)redir->content)->end_of_leaf == 0)
	{
		red = ((t_redir *)redir->content);
		cmd = get_curr_cmd(redir);
		i = -1;
		while (red->dest[++i])
			remove_quote(&(red->dest[i]));
		if (red->op_type == DBL_LESS)
		{
			tempfd = dup(STDOUT_FILENO);
			dup2(stdout, STDOUT_FILENO);
			fd = handle_hdoc(redir->content);
			dup2(tempfd, STDOUT_FILENO);
		}
		else
		{
			fd = open_file(redir->content);
			red->fd = fd;
		}
		if (fd != -1)
		{
			if (red->op_type == LESS
				|| red->op_type == DBL_LESS)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
		}
		temp = redir;
		redir = redir->next;
		ft_lstdelone(&temp, redir_delone);
	}
	expand_and_execute(cmd);
	// restore STDOUT & STDIN
	dup2(stdout, STDOUT_FILENO);
	dup2(stdin, STDIN_FILENO);
	if (redir)
	{
		g_shell->redir = redir->next;
		ft_lstdelone(&redir, redir_delone);
	}
	else
		g_shell->redir = redir;

}

void	ft_execute(t_ast *root, char **env)
{
	if (!root)
		return ;
	if (root->left)
		ft_execute(root->left, env);
	if (root->right)
		ft_execute(root->right, env);
	if (root->token->redir)
		handle_redir();
	else if (root->token->type == TOKEN_WORD)
		expand_and_execute(root->token->content);
	// search_pipe(root, ft_strdup("root"),env);
}

// void 	executor(char **argv, char **env)
// {
//
// }

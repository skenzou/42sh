/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:40:57 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/13 06:16:02 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		pipe_cmds(char **cmd1, char **cmd2, char **env);
void		search_pipe(t_ast *root,char *str, char **env);
void		redir_delone(void *data, size_t size);
void		ft_fork(char **cmd, char **env);
void		remove_quote(char **str);
char		*hash_table(char *str,char **env);

typedef struct s_hash_entry
{
	unsigned char *data;
	unsigned char *key;
}				t_hash_entry;

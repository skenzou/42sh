/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:53:00 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/14 06:34:30 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_ast		*ft_parse(t_list *lexer, t_list **redir);
void		del_ast(t_ast **root);
void		ft_execute(t_ast *root , char **env);
void 		print_redir(t_list *redir);
char		**realloc_new_tab(char *needle, char **old, size_t size);
char		**join_2tab(char **curr, char **next, size_t curr_size, size_t next_size);
char	 **dup_tab(char **tab, size_t size);

typedef struct		s_redir
{
	char			**dest;
	e_op_type		op_type;
	int				fd;
	char			end_of_leaf;
}					t_redir;

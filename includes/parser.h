/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:53:00 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/21 15:17:46 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_ast		*ft_parse(t_list *lexer);
void		del_ast(t_ast **root);
void 		print_redir(t_list *redir);
char		**realloc_new_tab(char *needle, char **old, size_t size);
char		**join_2tab(char **curr, char **next, size_t curr_size, size_t next_size);
char	 	**dup_tab(char **tab, size_t size);
t_ast		*newnode(t_token *token, t_list *pointer);
void		print_ast(t_ast *root,char *str);
void		create_redir_list(t_list *lexer);
void		join_all_redir(t_list *lexer);
char		*check_syntax_errors(t_list *tokens);
void		build_ast(t_list *lexer, t_ast **root, e_op_type optype);
void		handle_inhibitors(t_list *lexer);

typedef struct		s_redir
{
	char			**dest;
	e_op_type		op_type;
	int				fd;
	char			end_of_leaf;
}					t_redir;

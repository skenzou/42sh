/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:53:00 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/09 06:36:08 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_ast		*ft_parse(t_list *lexer);
void		del_ast(t_ast **root);
void		ft_execute(t_ast *root ,char **env);

typedef struct		s_redir
{
	char			*dest;
	e_op_type		op_type;
	int				fd;
}					t_redir;

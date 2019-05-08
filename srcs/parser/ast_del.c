/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 05:39:38 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/08 06:04:36 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "shell.h"

static void		del_one_ast(t_ast *root)
{
	ft_lstdelone(&root->list_pointer, lex_delone);
	free(root);
}

void 		del_ast(t_ast **root)
{
	if (!(*root))
		return ;
	if ((*root)->left)
		del_ast(&(*root)->left);
	if ((*root)->right)
		del_ast(&(*root)->right);
	del_one_ast(*root);
	*root = NULL;
}

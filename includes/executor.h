/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:40:57 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/08 00:43:17 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		pipe_cmds(char **cmd1, char **cmd2, char **env);
void		search_pipe(t_ast *root,char *str, char **env);
void		redirect(char **cmd, char *path, char **env, char simple);

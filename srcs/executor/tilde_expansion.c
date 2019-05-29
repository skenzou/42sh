/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:11:24 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/29 17:13:46 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void   tilde_expansion(char **ptr)
{
  char *str;
  char *home;
  char  buff[MAX_PATH_LEN];

  ft_bzero((void *)buff, MAX_PATH_LEN);
  str = *ptr;
  if (*str++ != '~')
    return ;
  home = get_homepath(g_shell->env);
  if (!home)
    home = "";
  if (!(*str))
    str = ft_strdup(home);
  else if (*str && *str != '/')
  {
    ft_strcpy(buff, "/Users/");
    ft_strcat(buff, str);
    if (check_dir(buff))
      return ;
    else
      str = ft_strdup(buff);
  }
  else
    str = ft_strjoin(home, str);
  if (!str)
    ft_exit("Malloc failed in tilde_expansion");
  free(*ptr);
  *ptr = str;
}

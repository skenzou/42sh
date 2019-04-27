/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:44:52 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/26 18:52:41 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"


/*
** petit example pour recuperer stdin & err dans un fork
*/
// int main(int argc, char **argv)
// {
// 	int fildes[2];
// 	pid_t pid;
// 	char **str;
// 	char buff[300];
//
// 	str = (char **)malloc(sizeof(char *) * 4);
// 	str[0] = ft_strdup("/bin/ls");
// 	str[1] = ft_strdup(".");
// 	str[2] = ft_strdup("hadhgawjh");
// 	str[3] = NULL;
// 	pipe(fildes);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(fildes[1], 1); /* recupere stdout */
// 		dup2(fildes[1], 2); /* recupere stderr */
// 		execve("/bin/ls", str, NULL);
// 	}
// 	else
// 	{
// 		wait(&pid);
// 		read(fildes[0], buff, 300);
// 		printf("buff: %s\n", buff);
// 	}
// 	return (0);
// }







/*
** REDIRECTION DANS UN FICHIER DONNER DANS ARGV[1]
*/
int main(int argc, char **argv)
{
	// int fildes[2];
	pid_t pid;
	char **str;
	char buff[300];

	int fd = open(argv[1], O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, 0666);
	str = (char **)malloc(sizeof(char *) * 4);
	str[0] = ft_strdup("/bin/ls");
	str[1] = ft_strdup(".");
	str[2] = ft_strdup("hadhgawjh");
	str[3] = NULL;
	// pipe(fildes);
	dup2(fd, 1); /* recupere stdout */
	dup2(fd, 2); /* recupere stderr */
	execve("/bin/ls", str, NULL);
	return (0);
}

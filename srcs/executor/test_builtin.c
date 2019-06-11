/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 00:34:44 by ghamelek          #+#    #+#             */
/*   Updated: 2019/06/11 12:55:31 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/stat.h>


static int is_integer(char *str,char *str2)
{
	int i;

	i = -1;
	while (str[++i] && ft_isdigit(str[i]))
		continue ;	
	if (str[i])
	{
		ft_putstr_fd("42sh: integer expression expected: ",2);
		ft_putendl_fd(str, 2);
		return(2);
	}
	i = -1;
	while (str2[++i] && ft_isdigit(str2[i]))
		continue ;	
	if (str2[i])
	{
		ft_putstr_fd("42sh: integer expression expected: ",2);
		ft_putendl_fd(str2, 2);
		return(2);
	}
	return (0);
}

static int	binary_test(char **av)
{
	if(!ft_strcmp(av[2],"=")) 								 
		return ((ft_strcmp(av[1],av[3]) != 0));
	else if (!ft_strcmp(av[2],"!=")) 								 
		return ((ft_strcmp(av[1],av[3]) == 0));
	else if (!ft_strcmp(av[2],"-eq")) 	
	{
		if(is_integer(av[1], av[3]) )
			return (2);
		else 
			return (!(ft_atoi(av[1]) == ft_atoi(av[3])));
	}
	else if (!ft_strcmp(av[2],"-ne"))						 
	{
		if(is_integer(av[1], av[3]) )
			return (2);
		else 
			return (ft_atoi(av[1]) == ft_atoi(av[3]));
	}
	else if (!ft_strcmp(av[2],"-ge")) 						 
	{
		if(is_integer(av[1], av[3]) )
			return (2);
		else	
			return (ft_atoi(av[1]) < ft_atoi(av[3]));
	}
	else if (!ft_strcmp(av[2],"-lt"))						 
	{
		if(is_integer(av[1], av[3]) )
			return (2);
		else	
			return (ft_atoi(av[1]) >= ft_atoi(av[3]));
	}
	else if (!ft_strcmp(av[2],"-le")) 						 
	{
		if(is_integer(av[1], av[3]) )
			return (2);
		else	
			return (ft_atoi(av[1]) > ft_atoi(av[3]));
	}
	else if(av[1][0] == '-')
	{	
		ft_putstr_fd("42sh: unknown condition: ",2);
		ft_putendl_fd(av[1], 2);
		return (2);
	}
	ft_putstr_fd("42sh: parse error: condition expected: ",2);
	ft_putendl_fd(av[1], 2);
	return (1);
}

static int	unary_test(char **av)
{
	struct stat *buf;
	int ret;

	buf = malloc(sizeof(struct stat));
	ret = lstat(av[2], buf);
	if(!ft_strcmp(av[1],"-b")) 								//teste 
		return (!((buf->st_mode & S_IFMT) == S_IFBLK));
	else if (!ft_strcmp(av[1],"-c"))						 //teste 
		return (!((buf->st_mode & S_IFMT) == S_IFCHR));
	else if (!ft_strcmp(av[1],"-d")) 						//teste 
		return (!((buf->st_mode & S_IFMT) == S_IFDIR));
	else if (!ft_strcmp(av[1],"-e"))    					//teste 
		return (!(ret == 0));
	else if (!ft_strcmp(av[1],"-f"))      					//teste 
		return (!(S_ISREG(buf->st_mode)));
	else if (!ft_strcmp(av[1],"-g")) 	//teste >> chmod g+s file ou chmod 2750 file 
		return (!(S_ISGID & buf->st_mode));
	else if (!ft_strcmp(av[1],"-L"))   	//teste 
		return (!(S_ISLNK(buf->st_mode)));
	else if (!ft_strcmp(av[1],"-p"))	// tested , create file with mkfifo to test 
		return (!((buf->st_mode & S_IFMT) == S_IFIFO));
	else if (!ft_strcmp(av[1],"-S")) //  tested create socket with c program 
		return (!(S_ISSOCK(buf->st_mode)));
	else if (!ft_strcmp(av[1],"-s"))     //tested 
		return (!(buf->st_size > 0));
	else if (!ft_strcmp(av[1],"-u"))	//teste >> chmod u+s file ou chmod 4644 file 
		return ((buf->st_mode & S_ISUID) == 0);
	else if (!ft_strcmp(av[1],"-r")) // tested , chmod 377 to disable read  
		return(access(av[2], R_OK) != 0);
	else if (!ft_strcmp(av[1],"-w"))     //tested 
		return((access(av[2], W_OK) != 0)); 
	else if (!ft_strcmp(av[1],"-x"))     //tested 
		return((access(av[2], X_OK) != 0)); 
	else if (!ft_strcmp(av[1],"-z"))     // tested 
		return ((ft_strlen(av[2]) != 0));   	
	else if(av[1][0] == '-')
	{	
		ft_putstr_fd("test: unknown condition: ",2);
		ft_putendl_fd(av[1], 2);
		return (2);
	}
		ft_putstr_fd("42sh: parse error: condition expected: ",2);
		ft_putendl_fd(av[1], 2);
	return (1);
}

int		test_builtin(int ac, char **av)
{
	int i = 0;
	int j ;
	int not ;

	while (av[++i] && !ft_strcmp(av[i],"!"))
		ft_strdel(&av[i]);
	not =  ((i - 1) && !(i % 2));
	ac = ac - i +  not;
	j = 1;
	while (i &&	av[i])
		av[j++] = av[i++];
	while(av[j])
		av[j++] = NULL;
	if(ac == 0)
		return(1);
	else if(ac == 1)
		return (not & (int)av[1]);
	else if(ac == 2)
	{
		if(not)
			return (not ^ (int)av[2]) ;
		return (unary_test(av));
	}
	else if(ac == 3)
		return (binary_test(av));
	else
		ft_putendl_fd("test: too many arguments",2);	
	return (5);
}

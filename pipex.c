/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:20:09 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/10/30 00:28:53 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_stdin(char *filepath)
{
	int fd;

	fd = open(filepath, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	execute_comand(char *argument)
{
	int		i;
	char	*compath;
	char	**comargs;

	comargs = ft_split(argument, ' ');
	compath = ft_strjoin("/bin/", comargs[0]);
	i = 0;
	i = execve(compath, comargs, NULL);
	if (i)
		perror(strerror(i));
	while (comargs[i++])
		free(comargs[i]);
	free(comargs);
}

int	main(int argc, char *argv[])
{
	int	pid[2];
	int pfd[2];
	
	pipe(pfd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		sleep(5);
		init_stdin(argv[1]);
		execute_comand(argv[2]);
		exit(0);
	}
	waitpid(0, &pid[1], WNOHANG);
	ft_printf("Process waited \n");
	return (argc);
}
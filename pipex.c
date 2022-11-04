/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:20:09 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/11/03 23:10:15 by lbiasuz          ###   ########.fr       */
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

void	dest_stdout(char *filepath)
{
	int fd;
	fd = open(filepath, O_WRONLY | O_TRUNC);
	dup2(STDOUT_FILENO, fd);
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
	i = 0;
	while (comargs[i++])
		free(comargs[i]);
	free(comargs);
	free(compath);
}

int	main(int argc, char *argv[])
{
	int	pid[2];
	int pfd[2];

	pipe(pfd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(pfd[0]);
		init_stdin(argv[1]);
		dup2(pfd[1], STDOUT_FILENO);
		if (argv[2])
			execute_comand(argv[2]);
		close(pfd[1]);
		exit(0);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		execute_comand(argv[3]);
		dest_stdout(argv[4]);
		close(pfd[0]);

	}
	return (argc);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:20:09 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/11/08 23:20:55 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	int	pfd[2];

	pipe(pfd);
	if (argc < 5)
		return (error("Sem argumentos o suficiente"));
	pid[0] = fork();
	if (pid[0] == -1)
		return (error("Falha no fork"));
	if (pid[0] == 0)
	{
		close(pfd[0]);
		init_stdin(argv[1]);
		dup2(pfd[1], STDOUT_FILENO);
		execute_comand(argv[2]);
		close(pfd[1]);
		exit(0);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		dest_stdout(argv[4]);
		execute_comand(argv[3]);
		close(pfd[0]);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:20:09 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/11/10 00:31:02 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_comand(char *argument, char **envp)
{
	int		i;
	int		errn;
	char	*compath;
	char	**comargs;
	
	comargs = ft_split(argument, ' ');
	compath = ft_strjoin("/bin/", comargs[0]);
	errn = execve(compath, comargs, envp);
	if (errn == -1)
		perror("Failed to execute command");
	i = 0;
	while (comargs[i++])
		free(comargs[i]);
	free(comargs);
	free(compath);
	if (errn == -1)
		exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[], char **envp)
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
		execute_comand(argv[2], envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		dest_stdout(argv[4]);
		execute_comand(argv[3], envp);
	}
	return (EXIT_SUCCESS);
}

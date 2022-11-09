/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 20:35:50 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/11/08 22:47:49 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_stdin(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		perror("Arquivo não encontrado");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	exit_stdout(char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_TRUNC);
	if (fd < 0)
	{
		perror("Arquivo não encontrado");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	free_command_args(char **args)
{
	int	i;

	while (args[i++])
		free(args[i]);
	free(args);
}

void	execute_command(char *argument)
{
	int		i;
	char	*command_path;
	char	**command_args;

	i = 0;
	command_args = ft_split(argument, ' ');
	command_path = ft_strjoin(BIN_PATH, command_args[0]);
	i = execve(command_path, command_args, NULL);
	free_command_args(command_args);
	free(command_path);
	if (i)
	{
		perror(strerror(i));
		exit(i);
	}
}

void	chain_commands(int fpid, char *argv[])
{
	int	pfd[2];
	int	npfd[2];
	int	pid[2];
	int	i;

	i = 1;
	pid[0] = fpid;
	if (pid[0] == 0)
		init_stdin(argv[i++]);
	while (argv[i + 1] && pid[0] == 0)
	{
		pipe(npfd);
		close(npfd[0]);
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		dup2(npfd[1], STDOUT_FILENO);
		pid[0] = fork();
		if (!pid[0])
			i++;
	}
	execute_command(argv[i]);
	if (!argv[i])
		exit_stdout(argv[i]);
	waitpid(pid[0], pid[1], 0);
	if (pid[0] != 0)
	{
		close(pfd[0]);
		close(npfd[1]);
	}
}

int	main(int argc, char *argv[])
{
	if (argc < 5)
		perror("Sem argumentos o suficiente");
}

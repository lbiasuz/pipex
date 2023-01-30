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

char	*command_path(char *envp[], char *command)
{
	char	**paths;
	char	*temp;
	int		i;

	i = 0;
	paths = ft_split(env_path(envp), ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], command);
		if (access(temp, X_OK) != -1)
			break ;
		free(temp);
		i++;
	}
	if (!paths[i])
		temp = NULL;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	free(command);
	return (temp);
}

void	execute_comand(char *argument, char *envp[])
{
	int		i;
	char	*compath;
	char	**comargs;

	i = 0;
	comargs = args_list(argument, 0);
	if (comargs[0][0] != '/')
		compath = command_path(envp, ft_strjoin("/", comargs[0]));
	else
		compath = ft_strjoin("", comargs[0]);
	if (!compath)
		error("command not found", 127);
	else if (execve(compath, comargs, envp) == -1)
		perror(strerror(errno));
	while (comargs[i] != NULL && *comargs[i] != '\0')
		free(comargs[i++]);
	free(comargs);
	if (!compath)
		exit(127);
	free(compath);
}

void	child(int pfd[2], char **argv, char **envp)
{
	close(pfd[0]);
	init_stdin(argv[1]);
	dup2(pfd[1], STDOUT_FILENO);
	execute_comand(argv[2], envp);
	exit(errno);
}

void	father(int pfd[2], int pid[2], char **argv, char **envp)
{
	waitpid(0, &pid[1], WEXITED);
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	dest_stdout(argv[4]);
	execute_comand(argv[3], envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	pid[2];
	int	pfd[2];

	if (argc < 5)
		return (error("Sem argumentos o suficiente", 1));
	if (pipe(pfd) == -1)
		return (error("Falha no pipe", 1));
	pid[0] = fork();
	if (pid[0] == -1)
		return (error("Falha no fork", 1));
	if (pid[0] == 0)
		child(pfd, argv, envp);
	else
		father(pfd, pid, argv, envp);
	return (errno);
}

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

char	*env_path(char *envp[])
{
	int	i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (envp[i])
		return (ft_strchr(envp[i], '=') + 1);
	return (NULL);
}

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
		if (access(temp, F_OK) != -1)
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

	comargs = ft_split(argument, ' ');
	if (comargs[0][0] != '/')
		compath = command_path(envp, ft_strjoin("/", comargs[0]));
	else
		compath = ft_strjoin("", comargs[0]);
	if (!compath)
		perror("command not found");
	else if (execve(compath, comargs, envp) == -1)
		perror(strerror(errno));
	i = 0;
	while (comargs[i] != NULL && *comargs[i] != '\0')
	{
		free(comargs[i]);
		i++;
	}
	free(comargs);
	free(compath);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	pid[2];
	int	pfd[2];

	if (argc < 5)
		return (error("Sem argumentos o suficiente"));
	if (pipe(pfd) == -1)
		return (error("Falha no pipe"));
	pid[0] = fork();
	if (pid[0] == -1)
		return (error("Falha no fork"));
	if (pid[0] == 0)
	{
		close(pfd[0]);
		init_stdin(argv[1]);
		dup2(pfd[1], STDOUT_FILENO);
		execute_comand(argv[2], envp);
		exit(errno);
	}
	else
	{
		waitpid(0, &pid[1], WEXITED);
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		dest_stdout(argv[4]);
		execute_comand(argv[3], envp);
	}
	return (errno);
}

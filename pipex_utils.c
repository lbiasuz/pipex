/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:20:00 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/11/14 05:37:29 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_stdin(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		perror("Arquivo não encontrado");
		exit(2);
	}
	dup2(fd, STDIN_FILENO);
}

void	dest_stdout(char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		perror("Arquivo não encontrado");
		exit(2);
	}
	dup2(fd, STDOUT_FILENO);
}

char	**args_list(char *args_str, int i)
{
	while (args_str[i])
	{
		if (args_str[i] == ' ')
			args_str[i] = -1;
		if (args_str[i] == 39 && ft_strchr_gnl(&args_str[i + 1], 39) != -1)
			i += ft_strchr_gnl(&args_str[i + 1], 39);
		i++;
	}
	return (ft_split(args_str, -1));
}

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

int	error(const char *str, int err)
{
	perror(str);
	return (err);
}

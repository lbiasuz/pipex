/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:20:00 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/11/10 00:34:55 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_stdin(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY | O_CLOEXEC);
	dup2(fd, STDIN_FILENO);
}

void	dest_stdout(char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CLOEXEC);
	dup2(fd, STDOUT_FILENO);
}

int	error(const char *str)
{
	perror(str);
	return (1);
}

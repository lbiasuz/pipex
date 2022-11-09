/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:20:00 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/11/08 23:21:00 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_stdin(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	dest_stdout(char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_TRUNC);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	error(const char *str)
{
	perror(str);
	return (-1);
}

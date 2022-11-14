/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:20:46 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/11/10 00:21:51 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"

# define BIN_PATH "/bin/"

int		main(int argc, char *argv[], char *env[]);
void	init_stdin(char *filepath);
void	dest_stdout(char *filepath);
char	**args_list(char *args_str, int i);
char	*env_path(char *envp[]);
int		error(const char *str, int err);
char	*command_path(char *envp[], char *command);
void	execute_comand(char *argument, char *env[]);
void	child(int pfd[2], char **argv, char **envp);
void	father(int pfd[2], int pid[2], char **argv, char **envp);

#endif

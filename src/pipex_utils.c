/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:47:32 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/21 17:36:12 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	handle_error(void)
{
	perror(strerror(errno));
	exit(1);
}

void	print_error(char *error, char *name)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\n", 2);
}

void	exec_cmds(int argc, char **argv, int is_here_doc)
{
	int	i;

	i = 2;
	if (is_here_doc)
		i++;
	while (i < argc - 2)
	{
		pipe_cmd(argv[i], -1);
		i++;
	}
}

void	redirect_file(char *file, int flags, mode_t mode, int newfd)
{
	int	filefd;

	filefd = open(file, flags, mode);
	if (filefd == -1)
		handle_error();
	if (dup2(filefd, newfd) == -1)
	{
		close(filefd);
		handle_error();
	}
	close(filefd);
}

void	check_permissions(int argc, char **argv, int is_here_doc)
{
	if (!is_here_doc)
	{
		if (access(argv[1], F_OK) == -1)
		{
			print_error("pipex: no such file or directory: ", argv[1]);
			exit(1);
		}
		else if (access(argv[1], R_OK) == -1)
		{
			print_error("pipex: permission denied: ", argv[1]);
			exit(1);
		}
	}
	if (access(argv[argc - 1], F_OK) == 0)
	{
		if (access(argv[argc - 1], W_OK) == -1)
		{
			print_error("pipex: permission denied: ", argv[argc - 1]);
			exit(1);
		}
	}
}

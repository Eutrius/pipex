/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:46:08 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/21 17:46:53 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	exec_cmd(char *cmd);
static void	redirect_stdout(int pipe[2], int outfd);

void	pipe_cmd(char *cmd, int outfd)
{
	pid_t	pid;
	int		new_pipefd[2];

	if (pipe(new_pipefd) == -1)
		handle_error();
	redirect_stdout(new_pipefd, outfd);
	pid = fork();
	if (pid == -1)
	{
		close(new_pipefd[0]);
		close(new_pipefd[1]);
		handle_error();
	}
	if (pid == 0)
		exec_cmd(cmd);
	wait(NULL);
	if (dup2(new_pipefd[0], STDIN_FILENO) == -1)
	{
		close(new_pipefd[0]);
		handle_error();
	}
	close(new_pipefd[0]);
}

static void	redirect_stdout(int pipe[2], int outfd)
{
	if (outfd != -1)
	{
		if (dup2(outfd, pipe[1]) == -1)
		{
			close(pipe[0]);
			close(pipe[1]);
			close(outfd);
			handle_error();
		}
		close(outfd);
	}
	if (dup2(pipe[1], STDOUT_FILENO) == -1)
	{
		close(pipe[0]);
		close(pipe[1]);
		handle_error();
	}
	close(pipe[1]);
}

static void	exec_cmd(char *cmd)
{
	char		**args;
	char		*path;
	extern char	**environ;

	args = ft_split(cmd, ' ');
	if (!args)
		handle_error();
	path = get_full_path(args[0], environ);
	if (!path)
	{
		ft_free_strs(args);
		handle_error();
	}
	if (execve(path, args, NULL) == -1)
	{
		ft_free_strs(args);
		exit(1);
	}
}

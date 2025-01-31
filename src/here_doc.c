/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:26:16 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/21 16:39:38 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	init_vars(char *name, char **limiter, int *openfd, int *readfd);
static void	read_line(char *limiter, int filefd, int print_prompt);

void	here_doc(char *lim)
{
	char	*limiter;
	int		openfd;
	int		readfd;

	init_vars(lim, &limiter, &openfd, &readfd);
	read_line(limiter, openfd, 1);
	if (dup2(readfd, STDIN_FILENO) == -1)
	{
		close(readfd);
		close(openfd);
		free(limiter);
		handle_error();
	}
	close(readfd);
}

static void	init_vars(char *lim, char **limiter, int *openfd, int *readfd)
{
	char	*filename;

	filename = ".here_doc";
	*openfd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*openfd == -1)
		handle_error();
	*readfd = open(filename, O_RDONLY);
	if (*readfd == -1)
	{
		close(*openfd);
		handle_error();
	}
	unlink(filename);
	*limiter = ft_strjoin(lim, "\n");
	if (!limiter)
	{
		close(*readfd);
		close(*openfd);
		handle_error();
	}
}

static void	read_line(char *limiter, int filefd, int print_prompt)
{
	char	*line;

	while (1)
	{
		if (print_prompt)
			ft_putstr_fd("pipex heredoc> ", STDOUT_FILENO);
		line = get_next_line(0);
		if (!line)
		{
			print_prompt = 0;
			continue ;
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			close(filefd);
			free(line);
			break ;
		}
		if (ft_strchr(line, '\n') != NULL)
			print_prompt = 1;
		ft_putstr_fd(line, filefd);
		free(line);
	}
	free(limiter);
}

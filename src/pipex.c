/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:17:32 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/21 16:31:19 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	is_here_doc;
	int	outfile_flag;

	if (argc < 5)
		return (0);
	is_here_doc = (ft_strcmp(argv[1], "here_doc") == 0);
	outfile_flag = O_TRUNC;
	if (is_here_doc && argc < 6)
		return (0);
	check_permissions(argc, argv, is_here_doc);
	if (is_here_doc)
	{
		here_doc(argv[2]);
		outfile_flag = O_APPEND;
	}
	else
		redirect_file(argv[1], O_RDONLY, 0, STDIN_FILENO);
	exec_cmds(argc, argv, is_here_doc);
	redirect_file(argv[argc - 1], O_WRONLY | O_CREAT | outfile_flag, 0644,
		STDOUT_FILENO);
	pipe_cmd(argv[argc - 2], STDOUT_FILENO);
	return (0);
}

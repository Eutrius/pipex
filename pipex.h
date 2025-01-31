/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:38:35 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/21 17:32:14 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>

void	check_permissions(int argc, char **argv, int is_here_doc);
void	here_doc(char *lim);
void	redirect_file(char *file, int flags, mode_t mode, int newfd);
void	exec_cmds(int argc, char **argv, int is_here_doc);
void	pipe_cmd(char *cmd, int outfd);
char	*get_full_path(char *cmd, char **env);
int		handle_error(void);
void	print_error(char *error, char *name);

#endif

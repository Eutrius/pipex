/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:17:25 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/21 17:53:28 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	**get_path_env(char *cmd, char **env);
static char	**append_cmd(char **paths, char *cmd);
static int	check_path(char *path);
static void	check_paths(char **paths, int *index, int *do_exist,
				char **full_path);

char	*get_full_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*full_path;
	int		do_exist;

	i = 0;
	full_path = cmd;
	do_exist = 0;
	paths = get_path_env(cmd, env);
	if (!paths)
		return (NULL);
	check_paths(paths, &i, &do_exist, &full_path);
	if (do_exist && paths[i] == NULL)
		print_error("pipex: permission denied: ", cmd);
	if (!do_exist && paths[i] == NULL)
		print_error("pipex: command not found: ", cmd);
	ft_free_strs(paths);
	return (full_path);
}

static void	check_paths(char **paths, int *index, int *do_exist,
		char **full_path)
{
	while (paths[*index] != NULL)
	{
		if (check_path(paths[*index]) == 1)
			*do_exist = 1;
		if (check_path(paths[*index]) == 2)
		{
			*full_path = ft_strdup(paths[*index]);
			break ;
		}
		(*index)++;
	}
}

static char	**get_path_env(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*init_path;
	char	**full_paths;

	i = 0;
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	init_path = ft_strdup(cmd);
	if (!init_path)
		return (NULL);
	paths = ft_split(&env[i][5], ':');
	if (!paths)
	{
		free(init_path);
		return (NULL);
	}
	full_paths = (ft_strscat(append_cmd(paths, cmd), init_path));
	if (!full_paths)
	{
		ft_free_strs(paths);
		free(init_path);
	}
	return (full_paths);
}

static char	**append_cmd(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	int		tmp_len;
	int		cmd_len;

	i = 0;
	cmd_len = ft_strlen(cmd);
	while (paths && paths[i] != NULL)
	{
		tmp_len = ft_strlen(paths[i]) + cmd_len + 2;
		tmp = (char *)ft_calloc(tmp_len, sizeof(char));
		if (!tmp)
		{
			ft_free_strs(paths);
			return (NULL);
		}
		ft_strlcat(tmp, paths[i], tmp_len);
		ft_strlcat(tmp, "/", tmp_len);
		ft_strlcat(tmp, cmd, tmp_len);
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
	return (paths);
}

static int	check_path(char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return (2);
	else if (access(path, F_OK) == 0)
		return (1);
	else
		return (0);
}

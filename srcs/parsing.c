/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:06:00 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/27 14:42:42 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	find_cmd_paths(t_pipex *pipex, char **env)
{
	pipex->env_path = NULL;
	while (*env && !pipex->env_path)
	{
		pipex->env_path = ft_strnstr(*env, "PATH=", 5);
		env++;
	}
	pipex->cmd_paths = ft_split(pipex->env_path + 5, ':');
	if (!pipex->cmd_paths)
	{
		free_array(pipex->cmd1);
		free_array(pipex->cmd2);
		return (ft_close(pipex));
	}
	return (0);
}

static int	get_cmd(t_pipex *pipex, char **argv)
{
	pipex->cmd1 = ft_split(argv[2], ' ');
	if (!pipex->cmd1)
		return (ft_close(pipex));
	if (ft_strncmp(pipex->cmd1[0], "awk", 3) == 0)
		handle_awk(argv[2], pipex->cmd1);
	pipex->cmd2 = ft_split(argv[3], ' ');
	if (!pipex->cmd2)
	{
		free_array(pipex->cmd1);
		return (ft_close(pipex));
	}
	if (ft_strncmp(pipex->cmd2[0], "awk", 3) == 0)
		handle_awk(argv[3], pipex->cmd2);
	return (0);
}

int	init_pipex(t_pipex *pipex, char **argv, char **env)
{
	pipex->fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->fd2 < 0)
		return (1);
	pipex->fd1 = open(argv[1], O_RDONLY);
	if (pipex->fd1 < 0)
	{
		close(pipex->fd2);
		return (1);
	}
	if (get_cmd(pipex, argv))
		return (1);
	if (find_cmd_paths(pipex, env))
		return (1);
	if (pipe(pipex->pipe) == -1)
	{
		perror("pipe : ");
		ft_close(pipex);
		return (1);
	}
	return (0);
}

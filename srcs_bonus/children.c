/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:01:47 by achansar          #+#    #+#             */
/*   Updated: 2023/01/26 16:09:27 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_cmd(t_pipex *pipex, char **cmd)
{
	int		i;
	char	*cmd_path;
	char	*join;

	i = 0;
	if (access(cmd[0], F_OK) == 0)
		return (cmd[0]);
	else
	{
		while (pipex->cmd_paths[i])
		{
			join = ft_strjoin(pipex->cmd_paths[i], "/");
			if (!join)
				return (NULL);
			cmd_path = ft_strjoin(join, cmd[0]);
			free(join);
			if (!cmd_path)
				return (NULL);
			if (access(cmd_path, F_OK) == 0)
				return (cmd_path);
			free(cmd_path);
			i++;
		}
	}
	return (NULL);
}

static int	child_one(t_pipex *pipex, char **env)
{
	char	*cmd;

	cmd = get_cmd(pipex, pipex->cmd1);
	if (!cmd)
	{
		cmd_not_found(pipex, pipex->cmd1[0]);
		exit(127);
	}
	close(pipex->pipe[0]);
	dup2(pipex->fd1, STDIN_FILENO);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	if (execve(cmd, pipex->cmd1, env) == -1)
		perror("execve ");
	return (0);
}

static int	child_two(t_pipex *pipex, char **env)
{
	char	*cmd;

	cmd = get_cmd(pipex, pipex->cmd2);
	if (!cmd)
	{
		printf("cmd2 = %s | arg = %s\n", pipex->cmd2[0], pipex->cmd2[1]);
		cmd_not_found(pipex, pipex->cmd2[0]);
		exit(127);
	}
	close(pipex->pipe[1]);
	dup2(pipex->pipe[0], STDIN_FILENO);
	dup2(pipex->fd2, STDOUT_FILENO);
	if (execve(cmd, pipex->cmd2, env) == -1)
		perror("execve ");
	return (0);
}

int	launch_processes(t_pipex *pipex, char **env)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		return (1);
	if (pipex->pid1 == 0)
	{
		child_one(pipex, env);
		printf("exit after 127\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipex->fd1);
		pipex->pid2 = fork();
		if (pipex->pid2 < 0)
			return (1);
		if (pipex->pid2 == 0)
		{
			child_two(pipex, env);
			exit(EXIT_SUCCESS);
		}
		else
			close(pipex->fd2);
		close_pipe(pipex);
	}
	return (0);
}

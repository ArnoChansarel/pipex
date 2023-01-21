/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:01:47 by achansar          #+#    #+#             */
/*   Updated: 2023/01/21 16:29:30 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_cmd(t_pipex *pipex, char **cmd)
{
	int		i;
	char	*cmd_path = NULL;
	char	*join = NULL;
	
	i = 0;
	while (pipex->cmd_paths[i])
	{
		join = ft_strjoin(pipex->cmd_paths[i], "/");//               => protect
		cmd_path = ft_strjoin(join, cmd[0]);//                    => protect
		// printf("cmd = %s\n", cmd_path);
		free(join);
		if (access(cmd_path, F_OK) == 0)
		{
			return (cmd_path);
		}	
		free(cmd_path);
		i++;	
	}
	return (NULL);
}

static int	child_one(t_pipex *pipex, char **env)
{
	char *cmd;
	
	cmd = get_cmd(pipex, pipex->cmd1);//                            => protect if return NULL
	close(pipex->pipe[0]);
	// printf("before execve1\n");
	dup2(pipex->fd1, STDIN_FILENO);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	if (execve(cmd, pipex->cmd1, env) == -1)
		perror("execve : ");
	return (0);
}

static int	child_two(t_pipex *pipex, char **env)
{
	char *cmd;

	cmd = get_cmd(pipex, pipex->cmd2);
	// char buff[100];
	close(pipex->pipe[1]);
	// read(pipex->pipe[0], buff, 21);
	// printf("before execve2, pipex contains : %s\n", buff);
	dup2(pipex->pipe[0], STDIN_FILENO);
	dup2(pipex->fd2, STDOUT_FILENO);
	if (execve(cmd, pipex->cmd2, env) == -1)
		perror("execve : ");
	return (0);
}

int	launch_processes(t_pipex *pipex, char **env)
{

	pipex->pid1 = fork();//                                      CHILD 1
	if (pipex->pid1 < 0)
	{
		printf("Fork 1 failed.\n");
		return (1);
	}
	if (pipex->pid1 == 0)
		child_one(pipex, env);
	else
	{
		waitpid(pipex->pid1, NULL, 0);
		close(pipex->fd1);
	}
	
	pipex->pid2 = fork();//                                      CHILD 2
	if (pipex->pid2 < 0)
	{
		printf("Fork 2 failed.\n");
		return (1);
	}
	if (pipex->pid2 == 0)
		child_two(pipex, env);
	else
	{
		// waitpid(pipex->pid2, NULL, 0);
		close(pipex->fd2);
	}
	return (0);
}
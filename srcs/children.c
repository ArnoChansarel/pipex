/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:01:47 by achansar          #+#    #+#             */
/*   Updated: 2023/01/31 15:57:47 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	child_infile(t_pipex *pipex, char *arg, char **env)
{
	char	*cmd;

	cmd = get_cmd(pipex, pipex->args, arg);
	if (!cmd)
	{
		cmd_not_found(pipex->command[0]);
		exit(127);
	}
	close(pipex->pipe[0]);
	dup2(pipex->fd1, STDIN_FILENO);
	close(pipex->fd1);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[1]);
	if (execve(cmd, pipex->command, env) == -1)
		perror("execve ");
	return (0);
}

static int	child_outfile(t_pipex *pipex, char *arg, char **env)
{
	char	*cmd;

	cmd = get_cmd(pipex, pipex->args, arg);
	if (!cmd)
	{
		cmd_not_found(pipex->command[0]);
		exit(127);
	}
	close(pipex->pipe[1]);
	dup2(pipex->fd2, STDOUT_FILENO);
	close (pipex->fd2);
	if (execve(cmd, pipex->command, env) == -1)
		perror("execve ");
	return (0);
}

static int	parent_process(t_pipex *pipex, t_arg *args)
{
	int	status;
	int	var;

	close(pipex->pipe[1]);
	if (args->i <= args->argc - 2)
	{
		dup2(pipex->pipe[0], STDIN_FILENO);
		close (pipex->pipe[0]);
	}
	else
		close (pipex->pipe[0]);
	waitpid(pipex->pid, &status, 0);
	if (args->i == args->argc - 2)
	{
		var = WEXITSTATUS(status);
		if (var)
		{
			exit(var);
		}
	}
	return (0);
}

int	launch_processes(t_pipex *pipex, t_arg *args)
{
	while (args->i < args->argc - 1)
	{
		if (pipe(pipex->pipe) == -1)
			return (1);
		pipex->pid = fork();
		if (pipex->pid < 0)
			return (1);
		else if (pipex->pid == 0)
		{
			if (args->i == 2)
				child_infile(pipex, args->argv[args->i], args->env);
			else
				child_outfile(pipex, args->argv[args->i], args->env);
		}
		else
			parent_process(pipex, args);
		args->i++;
	}
	return (0);
}

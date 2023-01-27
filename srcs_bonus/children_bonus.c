/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:01:47 by achansar          #+#    #+#             */
/*   Updated: 2023/01/27 15:54:31 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static int	child_infile(t_pipex *pipex, char *arg, char **env)
{
	char	*cmd;

	cmd = get_cmd1(pipex, arg, pipex->remplace_cmd1);
	if (!cmd)
	{
		cmd_not_found(pipex, pipex->remplace_cmd1[0]);
		exit(127);
	}
	close(pipex->pipe[0]);
	dup2(pipex->fd1, STDIN_FILENO);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	if (execve(cmd, pipex->remplace_cmd1, env) == -1)
		perror("execve ");
	return (0);
}

static int	child_middle(t_pipex *pipex, char *arg, char **env)
{
	char *cmd;

	cmd = get_cmd1(pipex, , pipex->remplace_cmd1);
	if (!cmd)
	{
		cmd_not_found(pipex, pipex->remplace_cmd1[0]);
		exit(127);
	}
	close(pipex->pipe[0]);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	if (execve(cmd, pipex->remplace_cmd1, env) == -1)
		perror("execve ");
	return (0);
}

static int	child_outfile(t_pipex *pipex, char *arg, char **env)
{
	char	*cmd;

	cmd = get_cmd1(pipex, arg, pipex->remplace_cmd1);
	if (!cmd)
	{
		cmd_not_found(pipex, pipex->remplace_cmd1[0]);
		exit(127);
	}
	close(pipex->pipe[1]);
	dup2(pipex->pipe[0], STDIN_FILENO);
	dup2(pipex->fd2, STDOUT_FILENO);
	if (execve(cmd, pipex->remplace_cmd1, env) == -1)
		perror("execve ");
	return (0);
}

static int	parent_process(t_pipex *pipex)
{
	int	status;
	int	var;

	waitpid(pipex->pid, &status, 0);
	if (WIFEXITED(status) != 0)
	{
		var = WEXITSTATUS(status);
		exit(var);
	}
	return (0);
}

int	launch_processes(t_pipex *pipex, t_arg args)
{
	int i;

	i = 1;
	while (i < args.argc - 1)
	{
		pipex->pid = fork();
		if (pipex->pid < 0)
			return (1);
		if (pipex->pid == 0)
		{
			if (i == 1)
			{
				child_infile(pipex, args.argv[i], args.env);
				exit(EXIT_SUCCESS);
			}
			else if (i == args.argc - 2)
			{
				child_outfile(pipex, args.argv[i], args.env);
				exit(EXIT_SUCCESS);
			}
			else
			{
				child_middle(pipex, args.argv[i], args.env);
				exit(EXIT_SUCCESS);
			}
		}
		else
			parent_process(pipex);
		i++;
	}
	return (0);
}







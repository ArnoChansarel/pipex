/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:06:00 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/31 14:29:52 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	handle_awk(char *argv, char **cmd)
{
	int	i;

	i = 1;
	while (*argv && (*argv != '\'' && *argv != '\"'))
		argv++;
	while (*argv && (*argv == '\'' || *argv == '\"'))
		argv++;
	cmd[i] = argv;
	while (*argv && (*argv != '\'' && *argv != '\"'))
		argv++;
	*argv = '\0';
	while (cmd[++i])
		cmd[i] = NULL;
	return (0);
}

static char	*check_cmd(t_pipex *pipex, char **cmd)
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
		free_array(pipex->command);
		return (ft_close(pipex));
	}
	return (0);
}

static int	get_instruction(t_pipex *pipex, char *cmd)
{
	pipex->command = ft_split(cmd, ' ');
	if (!pipex->command)
		return (ft_close(pipex));
	if (ft_strncmp(pipex->command[0], "awk", 3) == 0)
		handle_awk(cmd, pipex->command);
	return (0);
}

char	*get_cmd(t_pipex *pipex, t_arg args, char *cmd)
{
	char	*cmd_rtr;

	if (*cmd == '\0')
		return (NULL);
	cmd_rtr = NULL;
	if (get_instruction(pipex, cmd))
		return (NULL);
	if (find_cmd_paths(pipex, args.env))
		return (NULL);
	cmd_rtr = check_cmd(pipex, pipex->command);
	if (!cmd_rtr)
		return (NULL);
	return (cmd_rtr);
}

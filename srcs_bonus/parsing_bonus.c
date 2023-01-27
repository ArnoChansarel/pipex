/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:06:00 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/27 15:52:40 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
		free_array(pipex->remplace_cmd1);
		return (ft_close(pipex));
	}
	return (0);
}

static int	get_cmd2(t_pipex *pipex, char **argv)
{
	pipex->remplace_cmd1 = ft_split(argv[2], ' ');
	if (!pipex->remplace_cmd1)
		return (ft_close(pipex));
	if (ft_strncmp(pipex->remplace_cmd1[0], "awk", 3) == 0)
		handle_awk(argv[2], pipex->remplace_cmd1);
	return (0);
}

char	*get_cmd1(t_pipex *pipex, t_arg args, char **cmd)
{
	if (get_cmd2(pipex, args.argv))
		return (1);
	if (find_cmd_paths(pipex, args.env))
		return (1);
	return (check_cmd(pipex, pipex->remplace_cmd1));
}

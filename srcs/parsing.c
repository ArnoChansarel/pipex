/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnalove <arnalove@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:06:00 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/05 17:13:16 by arnalove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	find_cmd_paths(t_pipex *pipex, char **env)
{
	pipex->env_path = NULL;
	while(*env && !pipex->env_path)
	{
		pipex->env_path = ft_strnstr(*env, "PATH=", 5);
		env++;
	}
	// printf("line = %s\n", pipex->env_path);
	pipex->cmd_paths = ft_split(pipex->env_path + 5, ':');
	return (0);
}

int	parsing(t_pipex *pipex, char **argv)
{
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	return (0);
}

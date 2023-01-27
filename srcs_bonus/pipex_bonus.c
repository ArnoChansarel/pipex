/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:12:08 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/27 15:51:21 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
	if (pipe(pipex->pipe) == -1)
	{
		perror("pipe : ");
		ft_close(pipex);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (argc == 5)
	{
		pipex.args.argc = argc;
		pipex.args.argv = argv;
		pipex.args.env = env;
		if (init_pipex(&pipex, argv, env))
			return (1);
		launch_processes(&pipex, pipex.args);
		parent_waits(&pipex);
		ft_free_all(&pipex);
		return (0);
	}
	else
		return (1);
}

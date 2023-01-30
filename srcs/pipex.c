/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:12:08 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/30 12:05:25 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	pipex_init(t_pipex *pipex, int argc, char **argv, char **env)
{
	pipex->args.argc = argc;
	pipex->args.argv = argv;
	pipex->args.env = env;
	pipex->args.i = 2;
	pipex->fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->fd2 < 0)
		return (1);
	pipex->fd1 = open(argv[1], O_RDONLY);
	if (pipex->fd1 < 0)
	{
		close (pipex->fd2);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			pipex.args.here_doc = 1;
		else
			pipex.args.here_doc = 0;
		if (pipex_init(&pipex, argc, argv, env))
			return (1);
		launch_processes(&pipex, &pipex.args);
	}
	else
		return (1);
	return (0);
}

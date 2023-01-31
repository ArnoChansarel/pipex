/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:12:08 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/31 12:54:27 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	pipex_init(t_pipex *pipex, int argc, char **argv, char **env)
{
	pipex->args.argc = argc;
	pipex->args.argv = argv;
	pipex->args.env = env;
	pipex->args.i = 2;
	pipex->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->fd2 < 0)
	{
		perror(argv[argc - 1]);
		return (1);
	}
	pipex->fd1 = open(argv[1], O_RDONLY);
	if (pipex->fd1 < 0)
	{
		close (pipex->fd2);
		perror(argv[1]);
		return (1);
	}
	return (0);
}

int	error_msg(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (argc == 5)
	{
		if (pipex_init(&pipex, argc, argv, env))
			return (1);
		launch_processes(&pipex, &pipex.args);
	}
	else
		return (error_msg("Error : Correct usage is =>\n \
			./pipex input cmd1 cmd2 output\n"));
	return (0);
}

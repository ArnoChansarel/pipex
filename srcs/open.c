/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:36:01 by achansar          #+#    #+#             */
/*   Updated: 2023/01/31 15:33:25 by achansar         ###   ########.fr       */
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

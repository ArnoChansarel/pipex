/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:02:44 by achansar          #+#    #+#             */
/*   Updated: 2023/01/31 12:41:15 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	get_here_doc(t_pipex *pipex, char **argv)
{
	char	*line;

	pipex->fd1 = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0444);
	if (pipex->fd1 < 0)
		return (1);
	line = get_next_line(0);
	while (line)
	{
		write(pipex->fd1, line, ft_strlen(line));
		if (line)
			free(line);
		line = get_next_line(0);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
			break ;
	}
	free(line);
	close(pipex->fd1);
	return (0);
}

int	pipex_init(t_pipex *pipex, int argc, char **argv, char **env)
{
	pipex->args.argc = argc;
	pipex->args.argv = argv;
	pipex->args.env = env;
	pipex->args.i = 2;
	if (pipex->args.here_doc)
		pipex->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		pipex->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->fd2 < 0)
	{
		perror(argv[argc - 1]);
		return (1);
	}
	if (pipex->args.here_doc == 1)
		get_here_doc(pipex, argv);
	pipex->fd1 = open(argv[1], O_RDONLY);
	if (pipex->fd1 < 0)
	{
		close (pipex->fd2);
		perror(argv[1 + pipex->args.here_doc]);
		return (1);
	}
	return (0);
}

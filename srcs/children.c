/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:01:47 by achansar          #+#    #+#             */
/*   Updated: 2023/01/15 15:30:46 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	child_one(t_pipex *pipex, char **env)
{
	char *av[] = {
		"/bin/echo",
		"h_e_l_l_o_ _w_o_r_l_d",
		NULL,
	};
	close(pipex->pipe[0]);
	printf("before execve1\n");
	dup2(pipex->fd1, STDIN_FILENO);
	dup2(pipex->pipe[1], STDOUT_FILENO);
	if (execve(av[0], av, env) == -1)
		perror("execve : ");
	return (0);
}

int	child_two(t_pipex *pipex, char **env)
{
	char *av[] = {
		"/usr/bin/wc",
		NULL,
	};

	char buff[100];
	close(pipex->pipe[1]);
	read(pipex->pipe[0], buff, 21);
	printf("before execve2, pipex contains : %s\n", buff);
	dup2(pipex->pipe[0], STDIN_FILENO);
	dup2(pipex->fd2, STDOUT_FILENO);
	if (execve(av[0], av, env) == -1)
		perror("execve : ");
	return (0);
}

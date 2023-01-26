/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:26:43 by achansar          #+#    #+#             */
/*   Updated: 2023/01/26 18:34:38 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	handle_awk(char *argv, char **cmd)
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

int	cmd_not_found(t_pipex *pipex, char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	ft_free_all(pipex);
	return (0);
}

int	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (0);
}

int	ft_close(t_pipex *pipex)
{
	close(pipex->fd1);
	close(pipex->fd2);
	return (1);
}

int	close_pipe(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
	return (0);
}

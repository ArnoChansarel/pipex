/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:26:43 by achansar          #+#    #+#             */
/*   Updated: 2023/01/30 21:04:46 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

int	ft_free_all(t_pipex	*pipex)
{
	free_array(pipex->command);
	free_array(pipex->cmd_paths);
	return (1);
}

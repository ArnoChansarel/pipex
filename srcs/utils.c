/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:26:43 by achansar          #+#    #+#             */
/*   Updated: 2023/01/21 16:26:59 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

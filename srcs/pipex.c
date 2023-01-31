/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:12:08 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/31 14:36:45 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

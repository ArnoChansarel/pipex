/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:12:08 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/21 16:26:40 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// modele : file1 "cmd1" "cmd2" file2

/*
free() => tous ! + protections
gestion d'erreur
cas particuliers
*/

int main(int argc, char *argv[], char *env[])
{
	t_pipex pipex;

	if (argc == 5)
	{
		if (init_pipex(&pipex, argv, env))
			return (1);
		if (launch_processes(&pipex, env))
			return (1);
		close_pipe(&pipex);
		free_array(pipex.cmd1);
		free_array(pipex.cmd2);
		free_array(pipex.cmd_paths);
		return (0);
	}
	else
		return (1);
}

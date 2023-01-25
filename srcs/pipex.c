/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:12:08 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/25 19:45:57 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
/*
Probleme 1	: gerer les '', les "" et les '""' au parsing
			=> exemple : awk "'{count++} END {print count}'"
Probleme 2	: Get same error messages
Probleme 3	: Check env. Si vide, doit renvoyer 127, pas 11. Mais seulement si... pas clair


*/


int	parent_waits(t_pipex *pipex)
{
	int	status;
	int	var;
	
	waitpid(pipex->pid1, &status, 0);
	waitpid(pipex->pid2, &status, 0);
	if (WIFEXITED(status) != 0)
	{
		var = WEXITSTATUS(status);
		exit(var);
	}
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (argc == 5)
	{
		if (init_pipex(&pipex, argv, env))
			return (1);
		launch_processes(&pipex, env);
		parent_waits(&pipex);
		ft_free_all(&pipex);
		return (0);
	}
	else
		return (1);
}

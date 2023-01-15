/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:12:08 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/15 15:32:11 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
Quelle est la capacité max d'un pipe ? Faut-il le proteger ? Non.
*/

// modele : file1 "cmd1" "cmd2" file2
// edgecases :  pas ou trop d'arg
//				si file existe pas, proteger
//				si cmd n'existe pas ?
//				chemin d'acces files
// Il y a beaucoup des split dans la creation des commandes. Ne pas oubier
// de free() l4ensemble via une fonction, ou avant si plus opti.

int main(int argc, char *argv[], char *env[])
{
	t_pipex pipex;

	(void)argc;
	// CREATION PIPE
	if (pipe(pipex.pipe) == -1)
	{
		perror("pipe : ");//                      => commencer gestion d'erreur.
		exit(1);//                                => en comprendre tout le sens.
	}
	// OUVERTURE DES FILES
	pipex.fd1 = open(argv[1], O_RDONLY);
	if (!pipex.fd1)
		return (-1);
	pipex.fd2 = open(argv[4], O_WRONLY);
	if (!pipex.fd2)
		return (-1);
	
	// RECUPERATION DES COMMANDES + ARGS
	parsing(&pipex, argv);

	// AJOUT DES CHEMINS DE COMMANDE.
	find_cmd_paths(&pipex, env);

	// CHILD 1
	pipex.pid1 = fork();
	printf("pid1 = %d\n", pipex.pid1);
	if (pipex.pid1 < 0)
	{
		printf("Fork 1 failed.\n");
		return (-1);
	}
	if (pipex.pid1 == 0)//                  Soit branche fils.
		child_one(&pipex, env);

	// CHILD 2
	pipex.pid2 = fork();
	printf("1pid2 = %d\n", pipex.pid2);
	if (pipex.pid2 < 0)
	{
		printf("Fork 2 failed.\n");
		return (-1);
	}
	printf("2pid2 = %d\n", pipex.pid2);
	if (pipex.pid2 == 0)
	{
		printf("3pid2 = %d\n", pipex.pid2);
		child_two(&pipex, env);
	}
	// FREE ? 
	// 1. Les splits de creation

	// CLOSE FILES
	close(pipex.fd1);
	close(pipex.fd2);
	return (0);
}



// int	get_cmd(t_pipex *pipex)
// {
// 	char	*cmd;
	
// 	return (0);
// }
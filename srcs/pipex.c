/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnalove <arnalove@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:12:08 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/05 19:42:46 by arnalove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
Quelle est la capacité max d'un pipe ? Faut-il le proteger ?

*/
int child_process(int *fd)
{
	char buff[101];

	printf("Le fd write chez le fils est %d\n", fd[1]);
	close(fd[1]);
	read(fd[0], buff, 100);
	printf("Le fd read chez le fils est %d\n", fd[0]);
	close(fd[0]);
	printf("Le fils lis : %s", buff);
	return (0);
}

int parent_process(int *fd, char *file)
{
	printf("Le fd read chez le pere est %d\n", fd[0]);
	close(fd[0]);
	write(fd[1], file, 1000);
	printf("Le fd write chez le pere est %d\n", fd[1]);
	close(fd[1]);
	return (0);
}

// modele : file1 "cmd1" "cmd2" file2
// edgecases :  pas ou trop d'arg
//				si file existe pas, proteger
//				si cmd n'existe pas ?
//				chemin d'acces files

int main(int argc, char *argv[], char *env[])
{
	t_pipex pipex;

	(void)env;
	char buff[1000 + 1];

	if (pipe(pipex.fd) == -1)
		return (-1);//                      => commencer gestion d'erreur.

	pipex.fd1 = open(argv[1], O_RDONLY);
	if (!pipex.fd1)
		return (-1);
	pipex.fd2 = open(argv[4], O_WRONLY);
	if (!pipex.fd2)
		return (-1);
	
	parsing(argc, argv);
	find_cmd_paths(&pipex, env);
	printf("out arg = %s\n", pipex.cmd_paths[1]);
	read(pipex.fd1, buff, 1000);

	printf("le fd du file1 est %d\n", pipex.fd1);
	printf("le fd du file2 est %d\n", pipex.fd2);

	dup2(pipex.fd1, STDIN_FILENO);

	




	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
	{
		printf("Fork failed.\n");
		return (-1);
	}
	if (pipex.pid1 == 0)//                  Soit branche fils.
	{
		dup2(pipex.fd1, STDIN_FILENO);
		dup2(pipex.fd2, STDOUT_FILENO);
		// child_process(pipex.fd);
		execve(pipex.cmd, pipex.cmd_args, env);
	}
	//else//                           Soit branche père.
		// parent_process(pipex.fd, buff);
	close(pipex.fd1);
	return (0);
}

int	get_cmd(t_pipex *pipex)
{
	char	*cmd;
	
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:12:08 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/31 12:51:51 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	error_msg(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			pipex.args.here_doc = 1;
		else
			pipex.args.here_doc = 0;
		if (pipex_init(&pipex, argc, argv, env))
			return (1);
		launch_processes(&pipex, &pipex.args);
		unlink("here_doc");
		system("leaks pipex");
	}
	else
		return (error_msg("Error : Correct usage is =>\n \
			./pipex input cmd1 cmd2 ... cmd(n) output\n"));
	return (0);
}

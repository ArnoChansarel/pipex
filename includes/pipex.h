/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:12:22 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/31 14:37:02 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_arg {
	int		argc;
	char	**argv;
	char	**env;
	int		i;
	int		here_doc;
}	t_arg;

typedef struct s_pipex {
	pid_t	pid;
	int		pipe[2];
	char	*env_path;
	char	**cmd_paths;
	char	**command;
	char	*cmd;
	int		fd1;
	int		fd2;
	t_arg	args;
}	t_pipex;

/*PIPEX FUNCTIONS*/
int		init_pipex(t_pipex *pipex, char **argv);
int		launch_processes(t_pipex *pipex, t_arg *args);
char	*get_cmd(t_pipex *pipex, t_arg args, char *cmd);
int		pipex_init(t_pipex *pipex, int argc, char **argv, char **env);

/*UTILS*/
int		free_array(char **array);
int		ft_close(t_pipex *pipex);
int		close_pipe(t_pipex *pipex);
int		ft_free_all(t_pipex	*pipex);
int		cmd_not_found(char *cmd);

/*LIBFT FUNCTIONS*/
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif

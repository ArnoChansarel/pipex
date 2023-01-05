/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnalove <arnalove@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:12:22 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/05 19:22:50 by arnalove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#   define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_arg {
    char **arg;
}   t_arg;

typedef struct s_pipex {
    pid_t   pid1;
    pid_t   pid2;
    char    **cmd1;
    char    **cmd2;
    int     fd[2];
    char    *env_path;
    char    **cmd_paths;
    char    *cmd;
    char    *cmd_args;
    int     fd1;
    int     fd2;
}   t_pipex;

/*PIPEX FUNCTIONS*/
int	find_cmd_paths(t_pipex *pipex, char **env);
int	parsing(t_pipex *pipex, char **argv);

/*LIBFT FUNCTIONS*/
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif

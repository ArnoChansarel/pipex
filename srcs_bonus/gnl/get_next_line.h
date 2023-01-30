/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:36:15 by achansar          #+#    #+#             */
/*   Updated: 2023/01/30 19:26:05 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strdup_nl(char *s1);
int		ft_strlen_gnl(char *s);
int		ft_isin(char *str, int c);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	*ft_free_all_gnl(char *s1, char **s2);

#endif

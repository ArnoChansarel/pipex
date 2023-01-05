/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnalove <arnalove@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:32:45 by arnalove          #+#    #+#             */
/*   Updated: 2023/01/05 14:49:20 by arnalove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (src[len] != '\0')
	{
		while (src[i] != '\0' && i < dstsize -1)
		{
			if (dstsize > 0)
				dst[i] = src[i];
			i++;
			if (src[i] != '\0')
				len++;
		}
		len++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (len);
}

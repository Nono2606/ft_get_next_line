/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhussene <nhussene@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 09:23:44 by nhussene          #+#    #+#             */
/*   Updated: 2026/11/23 16:19:43 by nhussene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE = 100
#endif

char	*get_next_line(int fd)
{
	static char	*r;
	char		buf[BUFFER_SIZE + 1];
	char		*str;
	int			nb_read;
	size_t		len;

	if (fd == -1)
		return (NULL);
	
	len = 0;
	while (!ft_strrchr(r, '\n') || nb_read != 0)
	{
		r = ft_strjoin(r, buf);
		if (ft_strrchr(r, '\n'))
			break ;
		nb_read = read (fd, buf, BUFFER_SIZE);
	}
	str = malloc(ft_substr());
	if (r)
	{
		str = ;
		r = ft_substr(buf, len, BUFFER_SIZE);
	}
	else
	{
		str = ft_substr(buf, 0, len);
		r = ft_substr(buf, len, BUFFER_SIZE);
	}
	return (str);
}
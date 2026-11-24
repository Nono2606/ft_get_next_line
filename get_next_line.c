/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhussene <nhussene@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 09:23:44 by nhussene          #+#    #+#             */
/*   Updated: 2026/11/24 15:57:29 by nhussene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_and_stash(int fd, char *stash, char *buf)
{
	ssize_t		nb_read;
	size_t		i;
	char		*tmp;

	nb_read = -1;
	i = 0;
	while (!has_newline(stash, '\n', i) && nb_read != 0)
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read < 0)
			return (free(stash), NULL);
		if (nb_read == 0)
			return (stash);
		buf[nb_read] = '\0';
		i = ft_strlen(stash);
		tmp = ft_strjoin(stash, buf);
		free(stash);
		if (tmp == NULL)
			return (NULL);
		stash = tmp;
	}
	return (stash);
}

static char	*ft_extract_line(char *stash)
{
	char	*substring;
	size_t	i;
	size_t	len;

	if (!stash)
		return (NULL);
	i = 0;
	len = 0;
	while (stash[len])
		if (stash[len++] == '\n')
			break ;
	if (len == 0)
		return (NULL);
	substring = malloc((len * sizeof(char)) + 1);
	if (substring == NULL)
		return (NULL);
	while (i < len)
	{
		substring[i] = stash[i];
		i++;
	}
	return (substring[i] = '\0', substring);
}

static char	*ft_clear_stash(char *stash, size_t len)
{
	char	*tmp;
	size_t	i;

	if (!stash)
		return (NULL);
	i = 0;
	tmp = malloc(((ft_strlen(stash) - len) * sizeof(char)) + 1);
	if (tmp == NULL)
	{
		free(stash);
		return (NULL);
	}
	while (stash[i + len])
	{
		tmp[i] = stash[i + len];
		i++;
	}
	tmp[i] = 0;
	return (free(stash), stash = tmp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*str;
	char		*buf;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!has_newline(stash, '\n', 0))
		stash = ft_read_and_stash(fd, stash, buf);
	if (!stash)
		return (free(buf), NULL);
	str = ft_extract_line(stash);
	if (!str)
		return (free(buf), free(stash), stash = NULL, NULL);
	stash = ft_clear_stash(stash, ft_strlen(str));
	if (!stash)
		return (free(buf), free(str), NULL);
	free(buf);
	return (str);
}


int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	i = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("\e[36m%d : [\e[0m%s\e[36m\e[0m", i, line);
		free(line);
		i++;
	}
	printf("--- fin du fichier : %d lignes lues ---\n", i - 1);
	close(fd);
	return (0);
}
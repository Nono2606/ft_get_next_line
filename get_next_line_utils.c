/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhussene <nhussene@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 09:44:54 by nhussene          #+#    #+#             */
/*   Updated: 2026/11/23 12:57:50 by nhussene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup( const char *source)
{
	size_t		i;
	char		*str;

	if (!source)
		return (NULL);
	i = 0;
	str = malloc((ft_strlen(source) * sizeof(char)) + 1);
	if (str == NULL)
		return (NULL);
	while (source[i])
	{
		str[i] = source[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(const char *s, size_t start, size_t len)
{
	char	*substring;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substring = malloc((len * sizeof(char)) + 1);
	if (substring == NULL)
		return (NULL);
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

static char	*addstr(char *str, const char *join, size_t start)
{
	size_t	i;

	i = 0;
	while (join[i])
	{
		str[start + i] = join[i];
		i++;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	size_t		s1_len;
	char		*str;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	len = s1_len + ft_strlen(s2);
	str = malloc((len * sizeof(char)) + 1);
	if (str == NULL)
		return (NULL);
	addstr(str, s1, 0);
	addstr(str, s2, s1_len);
	str[len] = '\0';
	return (str);
}
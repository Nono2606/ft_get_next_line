/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhussene <nhussene@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 09:44:54 by nhussene          #+#    #+#             */
/*   Updated: 2026/11/24 15:48:22 by nhussene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	size_t		s1_len;
	char		*str;
	size_t		i;

	if (!s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	len = s1_len + ft_strlen(s2);
	str = malloc((len * sizeof(char)) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len)
	{
		str[i] = s2[i - s1_len];
		i++;
	}
	str[len] = '\0';
	return (str);
}

int	has_newline(const char *str, int c, size_t start)
{
	if (!str)
		return (0);
	if (start > ft_strlen(str))
		return (0);
	while (str[start])
	{
		if (str[start] == (char)c)
			return (1);
		start++;
	}
	return (0);
}

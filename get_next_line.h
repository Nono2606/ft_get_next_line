/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhussene <nhussene@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 09:57:19 by nhussene          #+#    #+#             */
/*   Updated: 2026/11/23 14:58:04 by nhussene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>


size_t	ft_strlen(const char *str);
char	*ft_substr(const char *s, size_t start, size_t len);
char	*get_next_line(int fd);
char	*ft_strdup( const char *source);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strrchr(const char *str, int c);

int	main(void); // temp

#endif
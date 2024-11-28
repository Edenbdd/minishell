/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:35:21 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/19 16:37:27 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>

int		gnl_strlen(char *str);

char	*gnl_strchr(char *s, int to_find);
char	*gnl_strdup(char *s);
char	*gnl_strjoin(char *s1, char *s2);
char	*filled_line(int fd, char *buffer, char *line);
char	*adjust_line(char *line);
char	*left_char(char *line);
char	*get_next_line(int fd);

void	*gnl_calloc(size_t nmemb, size_t size);

#endif

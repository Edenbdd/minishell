/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:12:40 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/19 18:30:54 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;
	char		*adjusted_line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = gnl_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = filled_line(fd, buffer, line);
	adjusted_line = adjust_line(line);
	if (!adjusted_line)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	line = left_char(line);
	if (!line || !line[0])
	{
		free(line);
		line = NULL;
	}
	return (adjusted_line);
}

char	*filled_line(int fd, char *buffer, char *line)
{
	int		val_read;

	if (!line)
		line = gnl_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!line)
		return (free(buffer), NULL);
	val_read = 1;
	while (val_read && !gnl_strchr(buffer, '\n'))
	{
		val_read = read(fd, buffer, BUFFER_SIZE);
		if (val_read == -1)
			return (free(buffer), free(line), NULL);
		if (val_read == 0)
			break ;
		buffer[val_read] = '\0';
		line = gnl_strjoin(line, buffer);
	}
	return (free(buffer), line);
}

char	*adjust_line(char *line)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (!line || !line[0])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	temp = gnl_calloc(sizeof(char), (i + 2));
	if (!temp)
		return (NULL);
	while (j <= i)
	{
		temp[j] = line[j];
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

char	*left_char(char *line)
{
	char	*temp;
	char	*from_n;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (free(line), NULL);
	from_n = gnl_strchr(line, '\n');
	if (from_n)
		temp = gnl_strdup(from_n);
	else
		temp = gnl_strdup(line);
	return (free(line), temp);
}
/*
int main(void)
{
	int	fd;
//	char	*str;
	int	i;

	i = 0;
	fd = open("test", O_RDONLY);
	while (i < 6)
	{
		printf("%s",get_next_line(fd));
		free(get_next_line(fd));
		i++;
	}
	while ((str = get_next_line(fd))) {
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);

}
*/

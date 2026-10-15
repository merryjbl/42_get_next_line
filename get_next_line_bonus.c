/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjebali <mjebali@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 17:34:32 by mjebali           #+#    #+#             */
/*   Updated: 2026/06/28 13:12:11 by mjebali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_line(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}

char	*read_line(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*tmp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(stash), NULL);
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
		{
			tmp = stash;
			stash = ft_strjoin(stash, buffer);
			free(tmp);
		}
	}
	free(buffer);
	return (stash);
}

char	*extract_line(char *stash)
{
	size_t	i;

	if (!stash || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (ft_substr(stash, 0, i));
}

char	*clean_stash(char *stash)
{
	char	*new_stash;
	size_t	i;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	if (stash[i] == '\n')
		i++;
	new_stash = ft_substr(stash, i, ft_strlen(stash) - i);
	free(stash);
	return (new_stash);
}
/*
int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;

	fd1 = open("text1.txt", O_RDONLY);
	fd2 = open("text2.txt", O_RDONLY);
	fd3 = open("text3.txt", O_RDONLY);
	line = get_next_line(fd1);
	printf("fd1: %s", line);
	free(line);
	line = get_next_line(fd2);
	printf("fd2: %s", line);
	free(line);
	line = get_next_line(fd3);
	printf("fd3: %s", line);
	free(line);
	line = get_next_line(fd1);
	printf("fd1: %s", line);
	free(line);
	line = get_next_line(fd2);
	printf("fd2: %s", line);
	free(line);
	line = get_next_line(fd3);
	printf("fd3: %s", line);
	free(line);
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/

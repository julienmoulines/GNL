/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jul.moulines@free.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:18:15 by jmouline          #+#    #+#             */
/*   Updated: 2022/11/20 14:29:51 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_realloc(char *buffer, size_t size)
{
	char	*tmp;

	tmp = malloc(ft_strlen(buffer));
	tmp = ft_memcpy(tmp, buffer, size);
	free(buffer);
	buffer = malloc(size);
	buffer = ft_memcpy(buffer, tmp, size);
	free(tmp);
	return (buffer);
}

char	*ft_good_buffer(int fd, char *buffer)
{
	char	*tmp;
	int		count_read;

	if (!buffer)
		buffer = malloc(1);
	tmp = malloc(BUFFER_SIZE + 1);
	count_read = 1;
	if (!tmp || !buffer)
		return (NULL);
	while (!ft_strchr(tmp, '\n') && count_read != 0)
	{
		count_read = read(fd, tmp, BUFFER_SIZE);
		if (count_read == -1)
			return (free(tmp), NULL);
		tmp[count_read] = 0;
		buffer = ft_realloc(buffer, ft_strlen(tmp) + ft_strlen(buffer));
		if (!buffer)
			return (NULL);
		buffer = ft_strjoin(buffer, tmp);
		if (!buffer)
			return (NULL);
	}
	free(tmp);
	return (buffer);
}

char	*ft_get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	i--;
	if (buffer[i++] == '\n')
		line[i] = buffer[i];
	line[i] = 0;
	if (!i)
		return (NULL);
	return (line);
}

char	*ft_next_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = malloc(ft_strlen(buffer) - i + 1);
	if (!str)
		return (NULL);
	i++;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = 0;
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer_final;

	if (!fd || BUFFER_SIZE <= 0)
		return (NULL);
	buffer_final = ft_good_buffer(fd, buffer_final);
	if (!buffer_final)
		return (NULL);
	line = ft_get_line(buffer_final);
	if (!line)
		return (NULL);
	buffer_final = ft_next_buffer(buffer_final);
	if (!buffer_final)
		return (NULL);
	return (line);
}

/*
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd;
	int i = 1;
	fd = open("test.txt", O_RDONLY);
	char *test;

	while (i < 10)
	{
		test = get_next_line(fd);
		if (!test)
			return (printf("Plus rien à afficher !\n"));
		printf("ligne %d : %s\n", i, test);
		free(test);
		i++;
	}
}*/
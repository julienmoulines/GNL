/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jul.moulines@free.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:57:38 by jmouline          #+#    #+#             */
/*   Updated: 2022/11/18 12:58:12 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_normed(char *s1, char *s2, char *dest)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	if (!dest)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	if (i < (len_s1 + len_s2))
	{
		while (i < len_s1)
		{
			dest[i] = s1[i];
			i++;
		}
		len_s1 = 0;
		while (s2[len_s1])
			dest[i++] = s2[len_s1++];
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*dest;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = calloc(len_s1 + len_s2 + 1, 1);
	if (!dest)
		return (NULL);
	dest = ft_strjoin_normed(s1, s2, dest);
	return (dest);
}

char	*ft_buffer(char *buff, int fd)
{
	int check_read;
	char	*str;

	str = malloc((BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	while (!ft_strchr(str, '\n') && check_read != 0)
	{
		check_read = read(fd, str, BUFFER_SIZE);
		if (check_read == -1)
		{
			free(str);
			return (NULL);
		}
		str[check_read] = 0;
		buff = ft_strjoin(buff, str);	
		//printf("%s\n", buff);
	}
	//free(str);
	return (buff);
}

char	*ft_ligne(char *ligne, char *buff)
{
	int	i;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	ligne = malloc(i + 2);
	i = 0;
	while (buff[i] != '\n' && buff[i])
	{
		ligne[i] = buff[i];
		i++;
	}
	ligne[i] = buff[i];	
	ligne[i + 1] = 0;
	//free(buff);
	return (ligne);
}

char	*ft_new_line(char *buff)
{
	int	i;
	int	j;
	char	*str;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	str = malloc(ft_strlen(buff) - i + 1);
	i++;
	while (buff[i])
		str[j++] = buff[i++];
	str[j] = 0;
	return (str);
}

char	*get_next_line(int fd)
{
	char	*ligne;
	static	char *buff;

	if (!fd)
		return (NULL);
	ligne = 0;
	buff = ft_buffer(buff, fd);
	if (!buff)
		return (NULL);
	ligne = ft_ligne(ligne, buff);
	buff = ft_new_line(buff);
	if (!ligne)
		return (NULL);
	return (ligne);
}

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	fd1 = open("test.txt", O_RDONLY);
	i = 1;
	while (i < 10)
	{
		line = get_next_line(fd1);
		printf("line [%d]: %s", i, line);
		//free(line);
		i++;
	}
	close(fd1);
	return (0);
}
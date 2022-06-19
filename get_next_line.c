/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:03:08 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/19 01:34:03 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static char	*add_read(int fd, char *rest);
static char	*make_line(char *src, size_t len);
static char	*store_rest(char *storage);

char	*get_next_line(int fd)
{
	static char	*storage;
	char	*line;
	
	if (fd < 0)
		return (NULL);
	if (!find_linebreak(storage))
		storage = add_read(fd, storage);
	line = make_line(storage, find_linebreak(storage));
	storage = store_rest(storage);
	return (line);
}

int	main(void)
{
	int		fd = open("test.txt", O_RDONLY);
	printf("\n=============LINE 1==============\n");
	char	*src = get_next_line(fd);
	printf("\n=============LINE 2==============\n");
	src = get_next_line(fd);
	printf("\n=============LINE 3==============\n");
	src = get_next_line(fd);
	printf("\n=============LINE 4==============\n");
	src = get_next_line(fd);
	printf("\n=============LINE 5==============\n");
	src = get_next_line(fd);
	printf("\n=============LINE 6==============\n");
	src = get_next_line(fd);
	printf("\n=============LINE 7==============\n");
	src = get_next_line(fd);
	printf("\n=============LINE 8==============\n");
	src = get_next_line(fd);
	printf("\n=============LINE 9==============\n");
	src = get_next_line(fd);
	printf("\n=============LINE 10==============\n");
	src = get_next_line(fd);
	printf("\n=============LINE 11==============\n");
	src = get_next_line(fd);
	printf("\n=============LINE 12==============\n");
	src = get_next_line(fd);
	printf("\n=============LINE 13==============\n");
	src = get_next_line(fd);
	/* printf("\n=============LINE 14==============\n");
	src = get_next_line(fd); */
	printf("%s", src);
}

static char	*add_read(int fd, char *rest)
{
	ssize_t	lenread;
	char	*line_read;
	char	*temp;
	char	*join;

	lenread = 1;
	join = ft_strjoin("", rest);
	rest = NULL;
	line_read = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (lenread >= 0)
	{
		lenread = read(fd, line_read, BUFFER_SIZE);
		if (join)
		{
			temp = ft_strjoin("", join);
			free(join);
		}
		join = ft_strjoin(temp, line_read);
		free(temp);
		if (lenread == 0 || find_linebreak(join))
			break;
	}
	free(line_read);
	return (join);
}

static char	*make_line(char *src, size_t len)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!len || !src)
		return (NULL);
	line = ft_calloc(len + 1, sizeof(char));
	while (i < len)
	{
		line[i] = src[i];
		i ++;
	}
	return (line);
}

static char	*store_rest(char *storage)
{
	char *temp;

	temp = ft_strjoin("", storage);
	if (storage)
	{
		free(storage);
		storage = NULL;
	}
	if (temp[find_linebreak(temp)])
		temp = ft_strjoin("", temp + find_linebreak(temp));
	else
	{
		free(temp);
		temp = NULL;
	}
	return (temp);
}

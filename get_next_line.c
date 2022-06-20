/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:03:08 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/20 11:09:51 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*add_read(int fd, char *storage);
static size_t	choose_length(const char *storage);
static char		*get_line(char *src, size_t len);
static char		*store_rest(char *storage, size_t len);

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	size_t		len;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!find_linebreak(storage))
		storage = add_read(fd, storage);
	len = choose_length(storage);
	line = get_line(storage, len);
	storage = store_rest(storage, len);
	return (line);
}

static char	*add_read(int fd, char *storage)
{
	ssize_t	lenread;
	char	*line_read;
	char	*temp;
	char	*join;

	lenread = 1;
	join = ft_strjoin(&storage, "");
	while (lenread >= 0)
	{
		line_read = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		lenread = read(fd, line_read, BUFFER_SIZE);
		if (join)
			temp = ft_strjoin(&join, "");
		join = ft_strjoin(&temp, line_read);
		if (lenread == 0 || find_linebreak(line_read))
			break ;
		if (line_read[0])
			free(line_read);
	}
	if (line_read)
		free(line_read);
	return (join);
}

static size_t	choose_length(const char *storage)
{
	if (!find_linebreak(storage))
		return (ft_strlen((char *)storage));
	else
		return (find_linebreak(storage));
}

static char	*get_line(char *src, size_t len)
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

static char	*store_rest(char *storage, size_t len)
{
	char	*new_storage;

	new_storage = NULL;
	if (storage[len])
		new_storage = ft_strjoin(&new_storage, storage + len);
	if (storage)
		free(storage);
	return (new_storage);
}

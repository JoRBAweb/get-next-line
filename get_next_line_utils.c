/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:37:10 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/19 03:25:25 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	length;

	length = 0;
	while (s && s[length] != '\0')
		length ++;
	return (length);
}

void	*ft_calloc(size_t num, size_t size)
{
	void			*buffer;
	unsigned char	*dst;
	size_t			total;

	total = num * size;
	buffer = malloc(total);
	if (buffer == NULL)
		return (NULL);
	dst = buffer;
	while (total > 0)
	{
		*dst = '\0';
		total --;
		dst ++;
	}
	return (buffer);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	if (!src)
		return (0);
	dstlen = ft_strlen(dst);
	srclen = ft_strlen((char *)src);
	i = dstlen;
	if (size <= dstlen)
		return (srclen + size);
	while (i < (size - 1) && *src)
		dst[i ++] = *src ++;
	dst[i] = '\0';
	return (dstlen + srclen);
}

char	*ft_strjoin(char **s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!*s1 && !s2)
		return (NULL);
	i = ft_strlen(*s1);
	j = ft_strlen(s2);
	join = ft_calloc((i + j + 1), sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_strlcat(join, *s1, i + 1);
	ft_strlcat(join, s2, i + j + 1);
	free(*s1);
	return (join);
}

size_t	find_linebreak(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\n')
	{
		if (s[i] == '\0')
			return (0);
		i ++;
	}
	return (i + 1);
}

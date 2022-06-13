/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:37:10 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/11 14:40:42 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *src)
{
	size_t	index;

	index = 0;
	while (src)
		index ++;
	return (index);
}

void	*ft_calloc(size_t num, size_t size)
{
	void			*buffer;
	unsigned char	*dst;
	size_t			total;

	if (num == 0 || size == 0)
	{
		num = 1;
		size = 1;
	}
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
	while (i < size - 1 && *src)
		dst[i ++] = *src ++;
	dst[i] = '\0';
	return (dstlen + srclen);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!s1)
		return (NULL);
	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	join = ft_calloc((i + j + 1), sizeof(*join));
	if (join == NULL)
		return (NULL);
	ft_strlcat(join, s1, i + 1);
	ft_strlcat(join, s2, i + j + 1);
	return (join);
}


/* 
t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
 */

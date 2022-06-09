/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:41:20 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/09 15:34:08 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 42

static size_t	ft_strlen(char *src);
static size_t	*has_linebreak(const char **line, char **rest, size_t lenread);

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	size_t		lenrest;
	size_t		lenread;

	lenrest = ft_strlen(rest);
	line = malloc((BUFFER_SIZE + lenrest + 1) * sizeof(*line));
	if (!line)
		return (NULL);
	lenread = read(fd, line + lenrest, BUFFER_SIZE);
	while(lenread)
	{
		if (has_linebreak(&line, &rest, lenread))
		{
			
		}
		lenread = read(fd, line + lenrest, BUFFER_SIZE);
	}
	
	return (line);
}

int	main(void)
{
	int		fd = open("test", O_RDONLY, 0);
	char	*src = get_next_line(fd);

	read(fd, src, 1);

	printf("%s", src);
}

static size_t	*has_linebreak(const char **line, char **rest, size_t lenread)
{
	size_t	i;

	i = 0;
	while (i < lenread)
	{
		if (*line[i] == '\n')
		{
			rest = (char *)&line[i + 1];
			line[i + 1] = '\0'; 
			return (1);
		}
		i ++;
	}
	return (0);
}

static size_t	ft_strlen(char *src)
{
	size_t	index;

	index = 0;
	while (src)
		index ++;
	return (index);
}

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

/* 
- criar var estática q recebe o resto dos caracteres q sobrarem depois do \n, 
inicialmente só terá um valor se tiver tido uma iteração anterior.
- criar string line q vai ser retornada no final da função
- criar size q será o tamanho inicialmente definido para line -> buffer_size + a len da estática

- alocar espaço de acordo com buffer + len de variavel estatica + 1 para o nulo

- ler arquivo de acordo com tamanho do buffer
- ler string preenchida e procurar '\n'
- var estática de ponteiro de char vai receber a sobra do depois do \n se tiver
- se não tiver sobra e ela tiver valor dar free nela
- por '\0' no final ou depois do '\n' se ele existir

 */
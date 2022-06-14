/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:41:20 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/14 20:18:04 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 42

/* static int	has_linebreak(char **line, char **rest, size_t lenread); */

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*final_line;
	size_t		lenread;

	line = ft_calloc(BUFFER_SIZE, sizeof(*line));
	if (!line)
		return (NULL);
	lenread = 1;
	while(lenread)
	{
		/* if (has_linebreak(&line, &rest, lenread))
			break ; */
		if (rest)
			final_line = ft_strjoin(final_line, rest);
		final_line = ft_strjoin(final_line, line);
		lenread = read(fd, line, BUFFER_SIZE);
		if (lenread < BUFFER_SIZE)
			line[lenread] = '\0';
	}
	return (final_line);
}

int	main(void)
{
	int		fd = open("test.txt", O_RDONLY);
	char	*src = get_next_line(fd);

	
	//char	*src = ft_calloc(BUFFER_SIZE + 1, sizeof(*src));
	//src[0] = '4';

	//read(fd, src + 1, BUFFER_SIZE);
		printf("%s", src);
}

/* static int	has_linebreak(char **line, char **rest, size_t lenread)
{
	size_t	i;

	i = 0;
	while (i < lenread)
	{
		if (*line[i] == '\n')
		{
			rest = &line[i + 1];
			*line[i + 1] = '\0'; 
			return (1);
		}
		i ++;
	}
	return (0);
} */

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:41:20 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/15 02:25:07 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 42

static char	*make_line(char *l, char *final, char **rest, size_t *lenread);

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*final_line;
	size_t		lenread;

	line = ft_calloc((BUFFER_SIZE + 1), sizeof(*line));
	if (!line)
		return (NULL);
	lenread = 1;
	final_line = ft_strjoin(final_line, rest);
	if (rest)
		free(rest);
	while(lenread > 0)
	{
		lenread = read(fd, line, BUFFER_SIZE);
		if (lenread < BUFFER_SIZE)
			line[lenread] = '\0';
		final_line = make_line(line, final_line, &rest, &lenread);
		if (rest || (lenread == 0))
			break ;
	}
	if (lenread < 0)
		return (NULL);
	if (line)
		free(line);
	return (final_line);
}

int	main(void)
{
	int		fd = open("test.txt", O_RDONLY);
	char	*src = get_next_line(fd);
	char	*src2 = get_next_line(fd);
	//src2 = get_next_line(fd);
	//src = get_next_line(fd);

	
	//char	*src = ft_calloc(BUFFER_SIZE + 1, sizeof(*src));
	//src[0] = '4';

	//read(fd, src + 1, BUFFER_SIZE);
		printf("primeira linha:\n%s", src2);
}

static char	*make_line(char *l, char *final, char **rest, size_t *lenread)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	if (l[i] == '\n')
		*lenread = 0;
	while (i < (*lenread - 1))
	{
		if (l[i] == '\n')
		{
			temp = ft_strjoin(*rest, l + (i + 1));
			while (temp[j] != '\0')
			{
				if (temp[j] == '\n')
				{
					temp[j] == '\0';
					*rest = ft_strjoin(*rest,temp);
				}
				j ++;
			}
			
			l[i + 1] = '\0';
			*lenread = 0;
			break ;
		}
		i ++;
	}
	final = ft_strjoin(final, l);
	return (final);
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
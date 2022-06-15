/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:41:20 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/15 14:19:03 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 42

static char	*make_line(char *l, char *final, char **rest, size_t *lenread);
static void	final_free(char **line, char **temp);

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*temp;
	char		*final_line;
	size_t		lenread;

	line = ft_calloc((BUFFER_SIZE + 1), sizeof(*line));
	temp = NULL;
	lenread = 1;
	if (!line)
		return (NULL);
	final_line = make_line(rest, final_line, &temp, &lenread);
	if (temp)
		rest = ft_strjoin("", temp);
	printf("print of inicial rest:\t|%s|\n",rest);
	while(lenread > 0)
	{
		lenread = read(fd, line, BUFFER_SIZE);
		if (lenread < BUFFER_SIZE)
			line[lenread] = '\0';
		final_line = make_line(line, final_line, &temp, &lenread);
		rest = ft_strjoin("", temp);
		printf("print of rest:\t|%s|\n", rest);
		if (lenread == 0)
			break ;
	}
	if (lenread < 0)
		return (NULL);
	final_free(&line, &temp);
	return (final_line);
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
	/* printf("\n=============LINE 4==============\n");
	src = get_next_line(fd); */

	printf("\n=============SAIDA NA MAIN ==============\n");
	printf("%s", src);
}

static char	*make_line(char *l, char *final, char **rest, size_t *lenread)
{
	size_t	i;
	char	*temp;

	i = 0;
	temp = NULL;
	printf("print of line:\t|%s|\n", l);
	if (!l)
		return (NULL);
	if (l[i] == '\n')
		*lenread = 0;
	while (i < ft_strlen(l))
	{
		if (l[i] == '\n')
		{
			i ++;
			temp = ft_strjoin(temp, l + i);
			printf("print of temp:\t|%s|\n", temp);
			l[i] = '\0';
			*lenread = 0;
			break ;
		}
		i ++;
	}
	*rest = ft_strjoin(*rest,temp);
	final = ft_strjoin(final, l);
	printf("print of final:\t|%s|\n", final);
	return (final);
}

static void	final_free(char **line, char **temp)
{
	if (*line)
		free(*line);
	if (*temp)
		free(*temp);
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
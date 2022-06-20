/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 08:20:45 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/20 10:19:04 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FD_MAX 4096

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(char *s);
void	*ft_calloc(size_t num, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strjoin(char **s1, char *s2);
char	*ft_strldup(const char *str, size_t len);
size_t	find_linebreak(const char *s);
char	*get_next_line(int fd);

#endif
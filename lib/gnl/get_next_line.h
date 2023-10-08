/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerrah <acerrah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:46:31 by acerrah           #+#    #+#             */
/*   Updated: 2023/02/14 14:13:01 by acerrah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*gnlft_substr(char const *s, unsigned int start, size_t len);
size_t	gnlft_strlen(const char *str);
char	*gnlft_strdup(const char *s1);
char	*get_left(char *left);
char	*get_line(char *buffer);
char	*gnlft_strchr(const char *s, int c);
char	*gnlft_strjoin(char *s1, char const *s2);
char	*get_buffer(int fd, char *left_str);

#endif

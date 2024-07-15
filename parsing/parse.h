/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:12:02 by belguabd          #+#    #+#             */
/*   Updated: 2024/07/12 12:15:29 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#ifndef COLORS_H
#define COLORS_H
#define RED "\033[31m"
#endif
typedef struct data 
{
    char **map;
} t_data;

int     ft_strcmp(char *str1, char *str2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	ft_putendl_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
int     ft_atoi(const char *str);
int	ft_isdigit(int c);
#endif
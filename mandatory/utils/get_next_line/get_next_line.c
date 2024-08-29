/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:37:07 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/29 12:58:49 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*get_new_save(char *save)
{
	char	*new_save;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (save[i] != '\n' && save[i])
		i++;
	if (save[i] == '\n')
		i++;
	while (!save[i])
		return (NULL);
	new_save = (char *)ft_malloc(ft_strlen(save) - i + 1, ALLOC);
	if (!new_save)
		return (save = NULL, NULL);
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	return (save = NULL, new_save);
}

static	char	*get_newline(char *save)
{
	char	*line;
	int		j;
	int		i;

	if (!save[0])
		return (NULL);
	i = 0;
	while (save[i] != '\n' && save[i])
		i++;
	if (save[i] == '\n')
		i++;
	line = (char *)ft_malloc((i + 1) * sizeof(char), ALLOC);
	if (!line)
		return (NULL);
	j = 0;
	while (save[j] != '\n' && save[j])
	{
		line[j] = save[j];
		j++;
	}
	if (save[j] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

static	bool	ft_check_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}

static char	*read_line(int fd, char *save)
{
	char	*buffer;
	int		stop_read;

	buffer = ft_malloc((size_t)(BUFFER_SIZE) + 1, ALLOC);
	if (!buffer)
		return (save = NULL, NULL);
	stop_read = 1;
	while (stop_read > 0)
	{
		stop_read = read(fd, buffer, BUFFER_SIZE);
		if (stop_read == -1)
			return (NULL);
		buffer[stop_read] = '\0';
		save = ft_strjoin(save, buffer);
		if (!save)
			break ;
		if (ft_check_newline(save))
			break ;
	}
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (0);
	if (!save)
		save = ft_strdup("");
	if (!save)
		return (NULL);
	save = read_line(fd, save);
	if (!save)
		return (NULL);
	line = get_newline(save);
	if (!line)
		return (save = NULL, NULL);
	save = get_new_save(save);
	return (line);
}

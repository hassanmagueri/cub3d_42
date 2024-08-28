/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:30:58 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/28 20:55:29 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_util_comma(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ',')
		i++;
	return (ft_substr(line, 0, i));
}

bool	is_direction(const char *str)
{
	return (!strcmp(str, "NO") || !strcmp(str, "SO")
		|| !strcmp(str, "WE") || !strcmp(str, "EA"));
}

bool	is_color(const char *str)
{
	return (!strcmp(str, "F") || !strcmp(str, "C"));
}

int	get_count_map(t_data *data, int i)
{
	int	count;

	count = 0;
	while (data->map_data[i])
	{
		count++;
		i++;
	}
	return (count);
}

void	load_map_data(t_data *data)
{
	char	*line;
	int		fd;
	int		i;
	char	*last_line;

	fd = open(data->map_path, O_RDONLY, 0666);
	if (fd < 0)
		ft_putendl_fd_color("Error\nOpen failure", 2, RED_E);
	data->map_data = (char **)ft_malloc(sizeof(char *)
			* (count_lines(data) + 1), ALLOC);
	i = 0;
	line = get_next_line(fd);
	if (!line)
		ft_putendl_fd_color("Error\nEmpty file", 2, RED_E);
	while (line)
	{
		last_line = line;
		data->map_data[i++] = remove_new_line(line);
		line = get_next_line(fd);
	}
	if (last_line[ft_strlen(last_line) - 1] == '\n')
		ft_putendl_fd_color("Error\nInvalid map", 2, RED_E);
	data->map_data[i] = NULL;
	close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:30:58 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/29 20:04:16 by belguabd         ###   ########.fr       */
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

bool	is_direction(char *str)
{
	return (!ft_strcmp(str, "NO") || !ft_strcmp(str, "SO")
		|| !ft_strcmp(str, "WE") || !ft_strcmp(str, "EA"));
}

bool	is_color(char *str)
{
	return (!ft_strcmp(str, "F") || !ft_strcmp(str, "C"));
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
		(ft_malloc(0, FREE), printf("Error\nOpen failure\n"));
	data->map_data = (char **)ft_malloc(sizeof(char *)
			* (count_lines(data) + 1), ALLOC);
	i = 0;
	line = get_next_line(fd);
	if (!line)
		(ft_malloc(0, FREE), close(fd), printf("Error\nEmpty file\n"));
	while (line)
	{
		last_line = line;
		data->map_data[i++] = remove_new_line(line);
		line = get_next_line(fd);
	}
	if (last_line[ft_strlen(last_line) - 1] == '\n')
		(ft_malloc(0, FREE), close(fd), print_error("Error\nInvalid map\n"));
	data->map_data[i] = NULL;
	close(fd);
}

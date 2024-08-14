/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:19:21 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/13 12:37:43 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	space_surrounded_one(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map.layout[y])
	{
		x = 0;
		while (data->map.layout[y][x])
		{
			if (data->map.layout[y][x] == 'N'
			|| data->map.layout[y][x] == 'S'
			|| data->map.layout[y][x] == 'E'
			|| data->map.layout[y][x] == 'W')
			{
				if (data->map.layout[y][x + 1] == '$'
					|| data->map.layout[y][x - 1] == '$'
					|| data->map.layout[y + 1][x] == '$'
					|| data->map.layout[y - 1][x] == '$')
					ft_putendl_fd_color("Error\nSpace is \
						not surrounded by '1'", 2, RED_E);
			}
			x++;
		}
		y++;
	}
}

void	invalid_character(t_data *data)
{
	int	count;
	int	x;
	int	y;

	(1) && (count = 0, y = 0);
	while (data->map.layout[y])
	{
		x = 0;
		while (data->map.layout[y][x])
		{
			if (check_character(data->map.layout[y][x]))
				ft_putendl_fd_color("Error\nInvalid \
					character in map", 2, RED_E);
			if (data->map.layout[y][x] == 'N'
				|| data->map.layout[y][x] == 'S'
				|| data->map.layout[y][x] == 'W'
				|| data->map.layout[y][x] == 'E')
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		print_error("Error\nMap must contain exactly \
		one start position ('N', 'S', 'E', or 'W')");
}

void	validate_zero_adjacent(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map.layout[y])
	{
		x = 0;
		while (data->map.layout[y][x])
		{
			if (data->map.layout[y][x] == '0')
			{
				if (data->map.layout[y][x + 1] == '$'
					|| data->map.layout[y][x - 1] == '$'
					|| data->map.layout[y + 1][x] == '$'
					|| data->map.layout[y - 1][x] == '$')
					print_error("Error\nInvalid map -\
						adjacent to '0' is a space");
			}
			x++;
		}
		y++;
	}
}

void	fill_line(t_data *data)
{
	char	*line;
	int		max_len;
	int		i;
	int		j;

	i = 0;
	max_len = ft_strlen(data->map.layout[find_longest_line_index(data)]);
	while (data->map.layout[i])
	{
		j = 0;
		line = (char *)ft_malloc(sizeof(char) * (max_len + 1), ALLOC);
		while (data->map.layout[i][j])
		{
			if (data->map.layout[i][j] == ' ')
				line[j] = '$';
			else
				line[j] = data->map.layout[i][j];
			j++;
		}
		while (j < max_len)
			line[j++] = '$';
		line[j] = '\0';
		data->map.layout[i++] = line;
	}
}

void	parse_map(t_data *data)
{
	int	i;
	int	y;

	validate_map(data);
	fill_line(data);
	validate_zero_adjacent(data);
	invalid_character(data);
	space_surrounded_one(data);
	y = 0;
	while (data->map.layout[y])
		y++;
	data->map.width = ft_strlen(data->map.layout[0]);
	data->map.height = y;
}

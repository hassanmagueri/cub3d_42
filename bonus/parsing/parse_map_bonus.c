/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:19:21 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/29 14:51:30 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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
			if (is_direction_character(data, x, y))
			{
				if (is_adjacent_to_dollar(data, x, y))
				{
					ft_malloc(FREE, FREE);
					print_error("Error\nInvalid map");
				}
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
				(ft_malloc(FREE, FREE), print_error("Error\n\
				Invalid character"));
			if (data->map.layout[y][x] == 'N' || data->map.layout[y][x] == 'S'
			|| data->map.layout[y][x] == 'W' || data->map.layout[y][x] == 'E')
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
	{
		ft_mamalloc(FREE, FREE);
		print_error("Error\nInvalid map");
	}
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
				if (is_adjacent_to_dollar(data, x, y))
				{
					ft_malloc(FREE, FREE);
					print_error("Error\nInvalid map -\
						adjacent to '0' is a space");
				}
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
	i = 0;
}

void	parse_map(t_data *data)
{
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

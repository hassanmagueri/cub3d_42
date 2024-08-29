/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_top_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:40:55 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/29 13:56:06 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	validate_colors(t_data *data)
{
	char	*clr;
	int		j;
	int		i;

	i = 0;
	while (data->clrs[i])
	{
		j = 0;
		clr = ft_strtrim(data->clrs[i], " ");
		if (clr[j + 1] != ' ')
		{
			ft_malloc(0, FREE);
			ft_putendl_fd_color("Error\nInvalid colors", 2, RED_E);
		}
		i++;
	}
	i = 0;
	while (data->clrs[i])
	{
		clr = ft_strtrim(data->clrs[i], " ");
		validate_color(clr);
		i++;
	}
}

void	validate_top_map(t_data *data)
{
	int	fd;
	int	i;
	int	j;

	data->top_map = (char **)ft_malloc(sizeof(char *) * 7, ALLOC);
	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		(ft_malloc(0, FREE), print_error("Error\nOpen failure"));
	i = 0;
	j = 0;
	while (data->map_data[i] && j < 6)
	{
		if (skip_spaces(data->map_data[i]))
		{
			i++;
			continue ;
		}
		if (data->map_data[i][0])
			data->top_map[j++] = data->map_data[i];
		i++;
	}
	data->top_map[j] = NULL;
	if (find_colors(data->top_map) || find_dirs(data->top_map))
		(close(fd), print_error("Error\nInvalid top map"));
	close(fd);
}

bool	check_color(char *line, char *to_find)
{
	if (ft_strcmp(get_first_char(line), to_find))
		return (false);
	return (true);
}

int	find_colors(char **data)
{
	int	count_clr;
	int	i;

	i = 0;
	count_clr = 0;
	while (data[i])
	{
		if (check_color(data[i], "F") || check_color(data[i], "C"))
			count_clr++;
		i++;
	}
	if (count_clr != 2)
		return (-1);
	return (0);
}

void	set_map(t_data *data)
{
	int	i;
	int	j;

	set_top_map(data);
	i = count_empty_lines(data->map_data, 6);
	data->map.layout = (char **)ft_malloc(sizeof(char *)
			* (get_count_map(data, i) + 1), ALLOC);
	j = 0;
	while (data->map_data[i])
	{
		data->map.layout[j++] = data->map_data[i];
		i++;
	}
	data->map.layout[j] = NULL;
	check_newline(data->map.layout);
}

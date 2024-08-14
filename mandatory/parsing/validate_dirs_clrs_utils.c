/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_dirs_clrs_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:02:08 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/12 22:30:31 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_dirs(char *line, char *to_find)
{
	if (ft_strcmp(get_two_char(line), to_find))
		return (false);
	return (true);
}

void	print_error(char *message)
{
	ft_putendl_fd_color(message, 2, RED_E);
}

int	validate_char(char chr)
{
	if (chr == '0'
		|| chr == 'N'
		|| chr == 'S'
		|| chr == 'W'
		|| chr == 'E')
		return (-1);
	return (0);
}

int	validate_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0'
			|| line[i] == 'N'
			|| line[i] == 'S'
			|| line[i] == 'W'
			|| line[i] == 'E')
			return (-1);
		i++;
	}
	return (0);
}

void	validate_map(t_data *data)
{
	char	*line;
	int		i;

	if (validate_line(data->map.layout[0])
		|| validate_line(data->map.layout[get_len_map(data) - 1]))
		print_error("Error\nInvalid character");
	i = 0;
	while (data->map.layout[i])
	{
		if (data->map.layout[i][0])
			line = ft_strtrim(data->map.layout[i], " ");
		if (validate_char(line[0]) || validate_char(line[ft_strlen(line) - 1]))
			print_error("Error\nInvalid character");
		i++;
	}
}

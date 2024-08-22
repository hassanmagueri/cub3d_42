/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:27:16 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/12 23:00:43 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	get_count_comma(char *clr)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (clr[i])
	{
		if (clr[i] == ',')
			count++;
		i++;
	}
	return (++count);
}

int	check_comma(char *clr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (clr[i])
	{
		if (clr[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (-1);
	return (0);
}

int	get_len_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.layout[i])
		i++;
	return (i);
}

bool	check_character(char c)
{
	return (c != '$'
		&& c != '0'
		&& c != '1'
		&& c != 'N'
		&& c != 'S'
		&& c != 'E'
		&& c != 'W');
}

void	ft_putendl_fd_color(char *s, int fd, char *color)
{
	write(fd, color, 5);
	ft_putendl_fd(s, fd);
	write(fd, "\033[0m", 4);
}

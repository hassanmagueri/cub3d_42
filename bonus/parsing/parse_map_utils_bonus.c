/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:49:01 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/29 14:49:31 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	is_direction_character(t_data *data, int x, int y)
{
	return (data->map.layout[y][x] == 'N'
		|| data->map.layout[y][x] == 'S'
		|| data->map.layout[y][x] == 'E'
		|| data->map.layout[y][x] == 'W');
}

int	is_adjacent_to_dollar(t_data *data, int x, int y)
{
	return (data->map.layout[y][x + 1] == '$'
		|| data->map.layout[y][x - 1] == '$'
		|| data->map.layout[y + 1][x] == '$'
		|| data->map.layout[y - 1][x] == '$');
}

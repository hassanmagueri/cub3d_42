/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:32:50 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/27 15:14:09 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	draw_doors(t_data *data, double wall_hit_x,
	double wall_hit_y, t_ray ray)
{
	size_t	map_x;
	size_t	map_y;

	map_x = (int)((wall_hit_x) / TILE_SIZE);
	map_y = (int)((wall_hit_y) / TILE_SIZE);
	if ((map_x > 0 && data->map.layout[map_y][map_x - 1] == 'C'
		&& ray.is_vr && ray.direct == -1)
		|| (map_x < data->map.width
			&& data->map.layout[map_y][map_x] == 'C' && ray.direct == 1)
		|| (map_y > 0 && data->map.layout[map_y - 1][map_x] == 'C'
			&& !ray.is_vr && ray.direct == -1))
		return (true);
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:32:50 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/24 14:33:50 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool draw_doors(double wall_hit_x, double wall_hit_y, t_ray ray, t_map map)
{
	int map_x;
	int map_y;

	map_x = (int)((wall_hit_x) / TILE_SIZE);
	map_y = (int)((wall_hit_y) / TILE_SIZE);
	if (
		(map.layout[map_y][map_x - 1] == 'C' && ray.direct == -1) ||
		(map.layout[map_y][map_x] == 'C' && ray.direct == 1) ||
		(map.layout[map_y - 1][map_x] == 'C' && ray.direct == -1))
		return true;
	return false;
}

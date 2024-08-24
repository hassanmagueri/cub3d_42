/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:34:56 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/24 13:35:14 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"

void close_doors(t_map map, int p_y, int p_x)
{
	if (p_y + 1 < map.height && p_x < map.width && p_y + 1 >= 0 && p_x >= 0)
		if (map.layout[p_y + 1][p_x] == 'O')
			map.layout[p_y + 1][p_x] = 'C';
	if (p_x + 1 < map.width && p_y < map.height && p_x + 1 >= 0 && p_y >= 0)
		if (map.layout[p_y][p_x + 1] == 'O')
			map.layout[p_y][p_x + 1] = 'C';
	if (p_y - 1 >= 0 && p_x < map.width && p_x >= 0 && p_y - 1 < map.height)
		if (map.layout[p_y - 1][p_x] == 'O')
			map.layout[p_y - 1][p_x] = 'C';
	if (p_x - 1 >= 0 && p_y < map.height && p_y >= 0 && p_x - 1 < map.width)
		if (map.layout[p_y][p_x - 1] == 'O')
			map.layout[p_y][p_x - 1] = 'C';
}

void open_doors(t_map map, int p_y, int p_x)
{
	if (p_y + 1 < map.height && p_x < map.width && p_y + 1 >= 0 && p_x >= 0)
		if (map.layout[p_y + 1][p_x] == 'C')
			map.layout[p_y + 1][p_x] = 'O';
	if (p_x + 1 < map.width && p_y < map.height && p_x + 1 >= 0 && p_y >= 0)
		if (map.layout[p_y][p_x + 1] == 'C')
			map.layout[p_y][p_x + 1] = 'O';
	if (p_y - 1 >= 0 && p_x < map.width && p_x >= 0 && p_y - 1 < map.height)
		if (map.layout[p_y - 1][p_x] == 'C')
			map.layout[p_y - 1][p_x] = 'O';
	if (p_x - 1 >= 0 && p_y < map.height && p_y >= 0 && p_x - 1 < map.width)
		if (map.layout[p_y][p_x - 1] == 'C')
			map.layout[p_y][p_x - 1] = 'O';
}
void doors(t_data *data , t_map map)
{
	int p_x;
	int p_y;
	
	p_x = (int)(data->player.x / TILE_SIZE);
	p_y = (int)(data->player.y / TILE_SIZE);
	if (mlx_is_key_down(data->mlx, MLX_KEY_O))
	{
		open_doors(map, p_y, p_x);
		update_player(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_C))
	{
		close_doors(map, p_y, p_x);
		update_player(data);
	}	
}
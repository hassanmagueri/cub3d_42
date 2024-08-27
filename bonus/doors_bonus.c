/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:34:56 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/26 14:35:29 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"

void validate_door_positions(t_data *data, int y)
{
	int		x;
	bool	x_door;
	bool	y_door;

	x = 0;
	while (x < data->map.width)
	{
		x_door = false;
		y_door = false;
		if (data->map.layout[y][x] == 'C')
		{
			if ((data->map.layout[y][x + 1] == '1' && data->map.layout[y][x - 1] == '1'))
				x_door = true;
			else if (data->map.layout[y + 1][x] == '1' && data->map.layout[y - 1][x] == '1')
				y_door = true;
			if (!x_door && !y_door)
				print_error("Error\nInvalid door");
		}
		x++;
	}
}
void parsing_doors(t_data *data)
{

	int x;
	int y;

	y = 0;
	while (y < data->map.height)
	{
		validate_door_positions(data, y);
		y++;
	}
}
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
	int	p_x;
	int	p_y;
	
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
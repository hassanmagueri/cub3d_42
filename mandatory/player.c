/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:32:10 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/27 17:36:30 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:51:11 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/27 15:31:51 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void set_player(t_data *data, char *map, int i)
{
	size_t j;
	size_t angle;

	angle = 0;
	j = 0;
	while (j < data->map.width)
	{
		if (map[j] == 'N' || map[j] == 'S' || map[j] == 'W' || map[j] == 'E')
		{
			if (map[j] == 'N')
				angle = 270;
			else if (map[j] == 'W')
				angle = 180;
			else if (map[j] == 'S')
				angle = 90;
			else if (map[j] == 'E')
				angle = 0;
			data->player = new_player(data, j * TILE_SIZE + TILE_SIZE / 2,
									  i * TILE_SIZE + TILE_SIZE / 2, angle);
			break;
		}
		j++;
	}
}

t_player	new_player(t_data *data, int x, int y, int angle)
{
	t_player	player;

	player.x = x;
	player.y = y;
	player.angle = degtorad(angle);
	player.rotation_angle = 0;
	player.rotation_speed = 3;
	player.walk_direction = 0;
	player.move_speed = 3;
	player.radius = P_RAD;
	data->player = player;
	return (player);
}

bool	is_wall(t_data *data, int x, int y)
{
	char		**map;
	int			player_radian;
	int			i;
	int			j;
	t_player	player;

	player = data->player;
	map = data->map.layout;
	player_radian = P_RAD - 2;
	x = x * SCALE;
	y = y * SCALE;
	i = y - player_radian;
	while (i <= y + player_radian)
	{
		j = x - player_radian;
		while (j <= x + player_radian)
		{
			if (map[(int)(i / SCALE_SIZE)][(int)(j / SCALE_SIZE)] == '1'
				|| map[(int)(i / SCALE_SIZE)][(int)(j / SCALE_SIZE)] == 'C')
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

int	update_player(t_data *data)
{
	t_player	*player;
	double		new_x;
	double		new_y;
	double		walk_inside;
	int			move_step;

	player = &data->player;
	player->angle += player->rotation_angle * ROT_SPEED;
	walk_inside = 0;
	if (abs(player->walk_direction) == 2)
	{
		player->walk_direction /= 2;
		walk_inside = degtorad(90);
	}
	move_step = player->walk_direction * MOVE_SPEED;
	new_x = player->x + (cos(player->angle + walk_inside) * move_step);
	new_y = player->y + (sin(player->angle + walk_inside) * move_step);
	if (!is_wall(data, new_x, new_y))
		(1) && (player->x = new_x, player->y = new_y);
	cast_rays(data, data->map, data->player, &data->rays);
	player->walk_direction = 0;
	player->rotation_angle = 0;
	return (1);
}

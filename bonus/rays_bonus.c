/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:10:59 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/27 04:30:58 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

int	cast_rays(t_data *data, t_map map, t_player player, t_ray (*rays)[NUM_RAYS])
{
	double	angle;
	int		i;
	t_ray	vr;
	t_ray	hr;

	i = 0;
	angle = player.angle - FOV / 2;
	while (i < NUM_RAYS)
	{
		hr = horizontal_ray(player, map, normalize_angle(angle));
		vr = vertical_ray(player, map, normalize_angle(angle));
		(*rays)[i] = low_ray(vr, hr);
		project_walls(data, (*rays)[i], i);
		angle += FOV / NUM_RAYS;
		i++;
	}
	return (0);
}

bool	still_in_ver(t_player player, t_map map, double dx, double ray_angle)
{
	return ((player.x + dx) <= (map.width * TILE_SIZE)
		&& (player.y + dx * tan(ray_angle)) <= (map.height * TILE_SIZE)
		&& (player.x + dx) >= 0 && (player.y + dx * tan(ray_angle)) >= 0);
}

bool	still_in_hor(t_player player, t_map map, double dy, double ray_angle)
{
	return ((player.x + dy / tan(ray_angle)) <= (map.width * TILE_SIZE)
		&& (player.y + dy) <= (map.height * TILE_SIZE)
		&& (player.x + dy / tan(ray_angle)) >= 0 && player.y + dy >= 0);
}

t_ray	vertical_ray(t_player player, t_map map, double ray_angle)
{
	int			direct;	
	double		dx;
	double		player_tile_x;
	double		player_x_distance;

	direct = 1;
	player_tile_x = (floor(player.x / TILE_SIZE) + 1) * TILE_SIZE;
	if (ray_angle > M_PI / 2 && ray_angle < M_PI * 1.5)
	{
		direct = -1;
		player_tile_x = floor(player.x / TILE_SIZE) * TILE_SIZE;
	}
	player_x_distance = (player_tile_x - player.x) * direct;
	dx = player_x_distance * direct;
	while (still_in_ver(player, map, dx, ray_angle))
	{
		if (check_is_wall(map, player,
				dx + add_pixel(direct), dx * tan(ray_angle)))
			return ((t_ray){dx, dx * tan(ray_angle), ray_angle, 1, direct});
		dx += (double)TILE_SIZE * direct;
	}
	return ((t_ray){DBL_MAX, DBL_MAX, ray_angle, 2, direct});
}

t_ray	horizontal_ray(t_player player, t_map map, double ray_angle)
{
	double		player_tile_y;
	double		player_y_distance;
	int			direct;
	double		dy;

	direct = -1;
	player_tile_y = floor((player.y) / TILE_SIZE) * TILE_SIZE;
	if (ray_angle < M_PI)
	{
		direct = 1;
		player_tile_y = (floor((player.y) / TILE_SIZE) + 1) * TILE_SIZE;
	}
	player_y_distance = (player_tile_y - player.y) * direct;
	dy = player_y_distance * direct;
	while (still_in_hor(player, map, dy, ray_angle))
	{
		if (check_is_wall(map, player,
				dy / tan(ray_angle), dy + add_pixel(direct)))
			return ((t_ray){dy / tan(ray_angle), dy, ray_angle, 0, direct});
		dy += (double)TILE_SIZE * direct;
	}
	return ((t_ray){DBL_MAX, DBL_MAX, ray_angle, 0, direct});
}

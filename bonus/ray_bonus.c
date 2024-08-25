/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:10:59 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/25 03:15:53 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <math.h>

double normalize_angle(double angle)
{
	double	res;

	res = fmod(angle, 2 * M_PI);
	if (res < 0)
		res += 2 * M_PI;
    return res;
}

t_ray low_ray(t_ray ver, t_ray hor)
{
	double hyp_ver;
	double hyp_hor;

	hyp_ver = pow(ver.dx, 2) + pow(ver.dy, 2);
	hyp_hor = pow(hor.dx, 2) + pow(hor.dy, 2);
	if (hyp_ver < hyp_hor)
		return ver;
	return hor;
}


// bool check_is_wall(t_map map, int x, int y, int direct)
bool check_is_wall(t_map map, t_player player, double x, double y)
{
	char	**layout;
	int		i;
	int		j;

	x += player.x;
	y += player.y;
	layout = map.layout;
	i = (int)y / TILE_SIZE;
	j = (int)x / TILE_SIZE;
	if (i < 0 || j < 0 || i >= map.height || j >= map.width)
		return false;
	if (layout[i][j] == '1' || layout[i][j] == 'C' )
		return (true);
	return (false);
}
int cast_rays(t_data *data, t_map map, t_player player , t_ray (*rays)[NUM_RAYS])
{
	double	angle;
	int		i;
	t_ray	vr;
	t_ray	hr;
	
	i = 0;
	angle = player.angle - FOV / 2;
	while (i < NUM_RAYS)
	{
		vr = vertical_ray(player, map, normalize_angle(angle));
		hr = horizontal_ray(player, map, normalize_angle(angle));
		(*rays)[i] = low_ray(vr, hr);
		project_walls(data, (*rays)[i],i);
		angle += FOV / NUM_RAYS;
		i++;
	}
	return 0;
}



t_ray vertical_ray(t_player player, t_map map, double ray_angle)
{
    double		player_tile_x;
	double		player_x_distance;
	int		direct;	
	double	dx;
	double	dy;

	direct = 1;
	player_tile_x = (floor(player.x / TILE_SIZE) + 1) * TILE_SIZE;
    if (ray_angle > M_PI / 2 && ray_angle < M_PI * 1.5)
	{
		direct = -1;
		player_tile_x = floor(player.x / TILE_SIZE) * TILE_SIZE;
    }
    player_x_distance = (player_tile_x - player.x) * direct;
    dx = player_x_distance * direct;
    int i = 1;
    while (i < map.width) {
		int plus = (direct == -1) ? -1: 0;
    	if (check_is_wall(map, player, dx + plus, dx * tan(ray_angle)))
		    break;
        dx += (double)TILE_SIZE * direct;
        i++;
    }
	return ((t_ray){dx, dx * tan(ray_angle), ray_angle, 1, direct});
}

t_ray	horizontal_ray(t_player player, t_map map, double ray_angle)
{
	double 		player_tile_y;
	double 		player_y_distance;
	int			direct;
	double		dy;
	double		dx;

	direct = -1;
	player_tile_y = floor((player.y) / TILE_SIZE) * TILE_SIZE;
	if (ray_angle < M_PI)
	{
		direct = 1;
		player_tile_y = (floor((player.y) / TILE_SIZE) + 1) * TILE_SIZE;
	}
	player_y_distance = (player_tile_y - player.y) * direct;
	dy = player_y_distance * direct;
	int i = 0;
	while (i < map.height)
	{
		int plus = (direct == -1) ? -1: 0;
		if (check_is_wall(map, player, dy / tan(ray_angle), dy + plus))
			break;
		dy += (double)TILE_SIZE * direct;
		i++;
	}
	return ((t_ray){dy / tan(ray_angle), dy, ray_angle, 0, direct});
}

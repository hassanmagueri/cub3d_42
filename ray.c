/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:10:59 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/01 22:26:47 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
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
	// hor.is_vr = 0;
	// ver.is_vr = 1;
	if (hyp_ver < hyp_hor)
		return ver;
	return hor;
}


bool check_is_wall(t_map map, int x, int y, int direct)
{
	char	**layout;
	int		i;
	int		j;
	
	layout = map.layout;
	i = y / TILE_SIZE;
	j = x / TILE_SIZE;
	if (i < 0 || j < 0 || i >= map.height || j >= map.width)
		return false;
	if (
		layout[i][j] == '1'
		// || (layout[i][j + 1 * direct] == '1' && layout[i + 1 * direct][j] == '1')
		// || (layout[i + 1 * direct][j] == '1' && layout[i][j - 1 * direct] == '1')
		)
		return (true);
	return (false);
}
int cast_rays(t_map map, t_player player , t_ray (*rays)[NUM_RAYS])
{
	double	angle;
	int		i;
	t_ray	vr;
	t_ray	hr;
	// t_ray	rays[NUM_RAYS];

	
	i = 0;
	angle = player.angle - FOV / 2;
	while (i < NUM_RAYS)
	{
		vr = vertical_ray(player, map, normalize_angle(angle));
		hr = horizontal_ray(player, map, normalize_angle(angle));
		(*rays)[i] = low_ray(vr, hr);
		draw_line(
			new_line(
				(t_point){(*rays)[i].dx + player.x, (*rays)[i].dy + player.y},
				(t_point){player.x,player.y}, SEMI_YELLOW),
				player.img
		);
		angle += FOV / NUM_RAYS;
		i++;
	}
	// rays = rays; 
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
	printf("direct = %d\n", direct);
    player_x_distance = (player_tile_x - player.x) * direct;
    dx = player_x_distance * direct;
	dy = dx * tan(ray_angle);
    int i = 1;
    while (i < map.width) {
		// *******
		// int plus = direct;
		int plus = (direct == -1) ? -1: 0;
		int new_dx =  player.x + dx + plus;
		int new_dy = player.y + dx * tan(ray_angle);
		// int new_dy = player.y + (dx + plus) * tan(ray_angle);
    	if (check_is_wall(map, new_dx, new_dy, 0))
		    break;
        dx += (double)TILE_SIZE * direct;
        dy = dx * tan(ray_angle);
        i++;
    }
	// if (direct == 1)
	// 	dx -= 1;
	return ((t_ray){dx, dy, ray_angle, 1, direct});
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
		player_tile_y = (floor(((int)player.y) / TILE_SIZE) + 1) * TILE_SIZE;
	}
	player_y_distance = (player_tile_y - player.y) * direct;
	dy = player_y_distance * direct;
	dx = dy / tan(ray_angle);
	int i = 0;
	double new_dy;
	double new_dx;
	while (i < map.height)
	{
		int plus = (direct == -1) ? -1: 0;
		// int plus = direct;
		new_dy = player.y + plus + dy; // * 10
		new_dx = player.x + dy / tan(ray_angle);
		// new_dx = player.x + (dy + plus) / tan(ray_angle);
		if (check_is_wall(map, new_dx, new_dy, 0))
			break;
		dy += (double)TILE_SIZE * direct;
		dx = dy / tan(ray_angle);
		i++;
	}
	
	// if (direct == 1)
	// 	dy -= 1;
	return ((t_ray){dx, dy, ray_angle, 0, direct});
}
// t_ray new_ray(t_data *data, double ray_angle)
// {
// 	int			len;
// 	double		dy;
// 	double		dx;
// 	t_ray		ray;
// 	t_line		line;
// 	t_player	player;
// 	int y_rect;

// 	player = data->player;
	
// 	printf("angle : %f\n", radtodeg(ray_angle));
// 	// y_rect = (((int)player.y / TILE_SIZE) + 1) * TILE_SIZE;
// 	y_rect = (((int)player.y / TILE_SIZE)) * TILE_SIZE;
	
// 	int playerYd = y_rect - player.y;
// 	// dy = (double)TILE_SIZE * 0 + playerYd;
// 	dy = -playerYd;
// 	dx = dy / tan(ray_angle);
// 	int i = 0;

// 	while (i < 14)
// 	{
// 		// if (is_wall(data->grid, player.x + (dy + 1)/tan(ray_angle), player.y + dy + 1))
// 		if (is_wall(data->grid, player.x - (dy - 1) / tan(ray_angle), player.y - dy - 1))
// 			break;
// 		// dy = (double)TILE_SIZE * i + playerYd;
// 		dy = (double)TILE_SIZE * i - playerYd + 1;
// 		dx = dy / tan(ray_angle);
// 		i++;
// 	}
// 	line = new_line(
// 		new_point(player.x, player.y),
// 		new_point(player.x - dx, player.y - dy),
// 		// new_point(player.x + dx, player.y + dy),
// 		SEMI_YELLOW
// 	);
// 	draw_line(line, player.img);
// 	return ray;
// }

// int	new_ray(t_data *data, double ray_angle)
// {
// 	int			len;
// 	double		dy;
// 	double		dx;
// 	t_ray		ray;
// 	t_line		line;
// 	t_player	player;
// 	int y_rect;

// 	player = data->player;
	
// 	printf("angle : %f\n", radtodeg(ray_angle));
// 	y_rect = (((int)player.y / TILE_SIZE) + 1) * TILE_SIZE;
	
// 	int playerYd = y_rect - player.y;
// 	dy = playerYd;
// 	dx = dy / tan(ray_angle);

// 	int i = 0;

// 	while (i < 14)
// 	{
// 		if (is_wall(data->grid, player.x + (dy + 1)/tan(ray_angle), player.y + dy + 1))
// 			break;
// 		dy = (double)TILE_SIZE * i + playerYd;
// 		dx = dy / tan(ray_angle);
// 		i++;		
// 	}
// 	// dy -= 1;
// 	// dx = dy / tan(ray_angle);
// 	printf("i: %d\n", i);
// 	printf("dy: %f\n", dy);
// 	printf("dx: %f\n", dx);
// 	printf("----------------------------------------\n");
// 	len = 100;
// 	line = new_line(
// 		new_point(player.x, player.y),
// 		new_point(player.x + dx, player.y + dy),
// 		SEMI_YELLOW
// 	);
// 	draw_line(line, player.img);
// 	return 0;
// }

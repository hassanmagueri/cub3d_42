/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:10:59 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/31 17:33:03 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

double normalize_angle(double angle)
{
	double	res;

	res = fmod(angle, 2 * M_PI);
	if (res < 0)
		res += 2 * M_PI;
    return res;
}

t_ray low_ray(t_ray ray1, t_ray ray2)
{
	double hyp1;
	double hyp2;

	hyp1 = pow(ray1.dx, 2) + pow(ray1.dy, 2);
	hyp2 = pow(ray2.dx, 2) + pow(ray2.dy, 2);
	// if (hyp1 == 0)
	// 	return ray2;
	// if (hyp2 == 0)
	// 	return ray1;
	if (hyp1 < hyp2)
		return ray1;
	return ray2;
}

int cast_rays(t_map map, t_player player , t_ray (*rays_ref)[NUM_RAYS])
{
	double	angle;
	int		i;
	t_ray	vr;
	t_ray	hr;
	// t_ray	rays[NUM_RAYS];

	
	i = 0;
	angle = player.angle - FOV / 2;
	while (i < 1)
	{
		vr = vertical_ray(player, map, normalize_angle(angle));
		hr = horizontal_ray(player, map, normalize_angle(angle));
		printf("ray: %d\n", i);
		(*rays_ref)[i] = low_ray(vr, hr);
		draw_line(
			new_line(
				(t_point){(*rays_ref)[i].dx + player.x, (*rays_ref)[i].dy + player.y},
				(t_point){player.x,player.y}, SEMI_YELLOW),
				player.img
		);
		angle += FOV / NUM_RAYS;
		i++;
	}
	// rays_ref = rays; 
	return 0;
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
	if (layout[i][j] == '1'
		|| (layout[i][j + 1 * direct] == '1' && layout[i + 1 * direct][j] == '1')
		|| (layout[i + 1 * direct][j] == '1' && layout[i][j - 1 * direct] == '1')
		)
		return (true);
	return (false);
}

t_ray vertical_ray(t_player player, t_map map, double ray_angle)
{
    int		player_tile_x;
	int		player_x_distance;
	int		direct;	
	double	dx;
	double	dy;

	direct = 1;
	player_tile_x = (((int)player.x / TILE_SIZE) + 1) * TILE_SIZE;
    if (ray_angle > M_PI / 2 && ray_angle < M_PI * 1.5) 
	{
		direct = -1;
		player_tile_x = ((int)player.x / TILE_SIZE) * TILE_SIZE;
    }
    player_x_distance = (player_tile_x - player.x) * direct;
    dx = player_x_distance * direct;
	dy = dx * tan(ray_angle);
    int i = 1;
    while (i < map.height) {
		int new_dx =  player.x + dx + direct;
		int new_dy = player.y + (dx + direct) * tan(ray_angle);
    	if (check_is_wall(map, new_dx, new_dy, 0))
		    break;
        dx += (double)TILE_SIZE * direct;
        dy = dx * tan(ray_angle);
        i++;
    }
	return ((t_ray){dx, dy, ray_angle});
}
t_ray	horizontal_ray(t_player player, t_map map, double ray_angle)
{
	int 		player_tile_y;
	int 		player_y_distance;
	int			direct;
	double		dy;
	double		dx;

	direct = -1;
	player_tile_y = (((int)player.y) / TILE_SIZE) * TILE_SIZE;
	if (ray_angle < M_PI)
	{
		direct = 1;
		player_tile_y = ((((int)player.y) / TILE_SIZE) + 1) * TILE_SIZE;
	}
	player_y_distance = (player_tile_y - player.y) * direct;
	dy = player_y_distance * direct;
	dx = dy / tan(ray_angle);
	int i = 0;
	double new_dy;
	double new_dx;
	while (i < map.width)
	{
		int n = direct;
		new_dy = player.y + direct + dy; // * 10
		new_dx = player.x + (dy + direct) / tan(ray_angle);
		if (check_is_wall(map, new_dx, new_dy, -direct))
			break;
		dy += (double)TILE_SIZE * direct;
		dx = dy / tan(ray_angle);
		
		i++;
	}
	return ((t_ray){dx, dy, ray_angle});
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

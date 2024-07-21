/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:10:59 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/21 19:25:01 by emagueri         ###   ########.fr       */
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

	hyp1 = pow(ray1.dx, 2) + pow(ray1.dx, 2);
	hyp2 = pow(ray2.dx, 2) + pow(ray2.dx, 2);
	if (hyp1 < hyp2)
		return ray1;
	return ray2;
}

int cast_rays(t_ray *rays, t_data *data)
{
	double	angle;
	int		i;
	t_player player;
	t_ray vr;
	t_ray hr;
	t_ray ray;

	player = data->player;
	i = 0;
	angle = player.angle - FOV / 2;
	while (i < NUM_RAYS)
	{
		vr = vertical_ray(data, normalize_angle(angle));
		hr = horizontal_ray(data, normalize_angle(angle));
		ray = low_ray(vr, hr);
		// ray = vr; // ??
		// ray = hr; // ??
		draw_line(
			new_line(
				new_point(ray.dx + player.x, ray.dy + player.y),
				new_point(player.x,player.y),SEMI_YELLOW
			),
			data->player.img
		);
		angle += FOV / NUM_RAYS;
		i++;
	}
	return 0;
}



t_ray vertical_ray(t_data *data, double ray_angle)
{
	double dx, dy;
    t_line line;
    t_player player;
    int player_tile_x, player_x_distance, direction;

    player = data->player;
	direction = 1;
	player_tile_x = (((int)player.x / TILE_SIZE) + 1) * TILE_SIZE;
    if (ray_angle > M_PI / 2 && ray_angle < M_PI * 1.5) {
		direction = -1;
		player_tile_x = ((int)player.x / TILE_SIZE) * TILE_SIZE;
    }
    player_x_distance = (player_tile_x - player.x) * direction;
    dx = player_x_distance * direction;
	dy = dx * tan(ray_angle);
    int i = 1;
    while (i < 14) {
		int new_dx =  player.x + dx + direction;
		int new_dy = player.y + (dx + direction) * tan(ray_angle);
    	if (is_wall(data->grid, new_dx, new_dy)
			|| (is_wall(data->grid, new_dx + TILE_SIZE * direction * -1, new_dy)
				&& is_wall(data->grid, new_dx, new_dy + TILE_SIZE * direction *- 1))
		)
		    break;
        dx = ((double)TILE_SIZE * i + player_x_distance) * direction;
        dy = dx * tan(ray_angle);
        i++;
    }
	t_ray ray = {dx, dy, ray_angle};
	return ray;
}
t_ray horizontal_ray(t_data *data, double ray_angle)
{
	int 		player_tile_y;
	int 		player_y_distance;
	int			direction;
	double		dy;
	double		dx;
	t_player	player;

	player = data->player;
	direction = -1;
	player_tile_y = ((((int)player.y) / TILE_SIZE)) * TILE_SIZE;
	if (ray_angle < M_PI)
	{
		direction = 1;
		player_tile_y = ((((int)player.y) / TILE_SIZE) + 1) * TILE_SIZE;
	}
	player_y_distance = (player_tile_y - player.y) * direction;
	dy = player_y_distance * direction;
	dx = dy / tan(ray_angle);
	int i = 0;
	while (i < 14)
	{
		double new_dx =player.x + (direction + dy) / tan(ray_angle);
		double new_dy = player.y + direction + dy;
		if (is_wall( data->grid, new_dx, new_dy)
			|| (is_wall( data->grid, new_dx + TILE_SIZE * -direction, new_dy)
			&& is_wall( data->grid, new_dx, new_dy + TILE_SIZE * -direction))
			|| (is_wall( data->grid, new_dx + TILE_SIZE * direction, new_dy)
			&& is_wall( data->grid, new_dx, new_dy + TILE_SIZE * -direction))
		)
			break;
		dy = ((double)TILE_SIZE * i + player_y_distance) * direction;
		dx = dy / tan(ray_angle);
		i++;
	}
	t_ray ray = {dx, dy, ray_angle};
	return (ray);
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

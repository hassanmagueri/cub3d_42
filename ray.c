/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:10:59 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/21 11:37:10 by emagueri         ###   ########.fr       */
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

int cast_rays(t_ray *rays, t_data *data)
{
	double	angle;
	int		i;
	t_player player;

	player = data->player;
	i = 0;
	angle = player.angle - FOV / 2;
	while (i < NUM_RAYS)
	{
		// vertical_ray(data, normalize_angle(angle));
		horizontal_ray(data, normalize_angle(angle));
		angle += FOV / NUM_RAYS;
		i++;
	}
	return 0;
}



int vertical_ray(t_data *data, double ray_angle)
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
    // player_x_distance = (player_tile_x - player.x);
    dx = player_x_distance * direction;
	printf("direction: %d\n", direction);
	printf("player.x: %f\n", player.x);
	printf("player_tile_x: %d\n", player_tile_x);
	printf("player_x_distance: %d\n", -player_x_distance);
    dy = dx * tan(ray_angle);
	
    int i = 1;
    while (i < 14) {
    	if (is_wall(data->grid, player.x + dx + direction, player.y + dy + direction)) 
		    break;
    	// if (is_wall(data->grid, player.x + dx + 1, player.y + dy + 1)) 
        // dx = ((double)TILE_SIZE * i + player_x_distance);
        dx = ((double)TILE_SIZE * i + player_x_distance) * direction;
        dy = dx * tan(ray_angle);
        i++;
    }
	printf("i: %d\n", i);
	printf("x: %f\n", dx);
    line = new_line(
        new_point(player.x, player.y),
        new_point(player.x + dx, player.y + dy),
        SEMI_YELLOW
    );
	printf("angle : %f\n", radtodeg(ray_angle));
	printf("-----------------------------------\n");
    draw_line(line, player.img);
	return 0;
}
int horizontal_ray(t_data *data, double ray_angle)
{
	double		dy;
	double		dx;
	t_line		line;
	t_player	player;
	int player_tile_y;
	int player_y_distance;



	player = data->player;
	int direction = -1;
	player_tile_y = ((((int)player.y) / TILE_SIZE)) * TILE_SIZE;
	if (ray_angle < M_PI)
	{
		direction = 1;
		player_tile_y = ((((int)player.y + 1) / TILE_SIZE)) * TILE_SIZE;
	}
	player_y_distance = (player_tile_y - player.y) * direction;
	dy = -player_y_distance;
	// dy = ((double)TILE_SIZE * 0 + player_y_distance) * direction
	dx = dy / tan(ray_angle);
	int i = 1;
	while (i < 14)
	{
		if (is_wall(data->grid, player.x + dx,
				player.y + dy))
			break;
		dy = ((double)TILE_SIZE * i + player_y_distance) * direction;
		dx = dy / tan(ray_angle);
		i++;
	}
	
	printf("player_y_distance: %d\n", player_y_distance);
	printf("dy: %f\n", dy);
	printf("i: %d\n", i);
	printf("--------------------------------\n");
	line = new_line(
		new_point(player.x, player.y),
		new_point(player.x + dx, player.y + dy),
		SEMI_YELLOW
	);
	draw_line(line, player.img);
	return (0);
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
// 	// dy = playerYd;
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
// 	return ray;
// }

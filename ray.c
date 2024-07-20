/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:10:59 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/20 10:03:42 by emagueri         ###   ########.fr       */
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
		new_ray(data, normalize_angle(angle));
		angle += FOV / NUM_RAYS;
		i++;
	}
	return 0;
}

t_ray new_ray(t_data *data, double ray_angle)
{
	int			len;
	double		dy;
	double		dx;
	t_ray		ray;
	t_line		line;
	t_player	player;
	int y_rect;

	player = data->player;
	
	printf("angle : %f\n", radtodeg(ray_angle));
	// y_rect = (((int)player.y / TILE_SIZE) + 1) * TILE_SIZE;
	y_rect = (((int)player.y / TILE_SIZE)) * TILE_SIZE;
	
	int playerYd = y_rect - player.y;
	// dy = playerYd;
	dy = -playerYd;
	dx = dy / tan(ray_angle);
	int i = 0;

	while (i < 14)
	{
		// if (is_wall(data->grid, player.x + (dy + 1)/tan(ray_angle), player.y + dy + 1))
		if (is_wall(data->grid, player.x - (dy - 1) / tan(ray_angle), player.y - dy - 1))
			break;
		// dy = (double)TILE_SIZE * i + playerYd;
		dy = (double)TILE_SIZE * i - playerYd + 1;
		dx = dy / tan(ray_angle);
		i++;
	}
	line = new_line(
		new_point(player.x, player.y),
		new_point(player.x - dx, player.y - dy),
		// new_point(player.x + dx, player.y + dy),
		SEMI_YELLOW
	);
	draw_line(line, player.img);
	return ray;
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

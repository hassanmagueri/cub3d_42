/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:10:59 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/17 15:32:09 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

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
		new_ray(data, angle);
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
	y_rect = (((int)player.y / TILE_SIZE) + 1) * TILE_SIZE;
	
	int playerYd = y_rect - player.y;
	dy = (double)TILE_SIZE * 0 + playerYd;
	dx = dy / tan(ray_angle);

	int i = 0;

	while (i < 14)
	{
		if (is_wall(data->grid, player.x + dx, player.y + dy))
			break;
		dy = (double)TILE_SIZE * i + playerYd;
		dx = dy / tan(ray_angle);
		i++;		
	}
	printf("----------------------------------------\n");
	len = 100;
	line = new_line(
		new_point(player.x, player.y),
		new_point(player.x + dx, player.y + dy),
		SEMI_YELLOW
	);
	draw_line(line, player.img);
	return ray;
}

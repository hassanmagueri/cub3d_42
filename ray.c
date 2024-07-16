/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:10:59 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/16 02:27:20 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int cast_rays(t_ray *rays, t_player player)
{
	double	angle;
	int		i;

	i = 0;
	angle = player.angle - FOV / 2;
	while (i < NUM_RAYS)
	{
		new_ray(player, angle);
		angle += FOV / NUM_RAYS;
		i++;
	}
	return 0;
}

t_ray new_ray(t_player player, double ray_angle)
{
	t_ray	ray;
	t_line	line;
	int		len;

	printf("player x: %f", player.x);
	printf(", y: %f\n", player.y);
	int offset = (TILE_SIZE * 5) + (player.x / TILE_SIZE);
	len = 100;
	line = new_line(
		new_point(player.x, player.y),
		new_point(
			player.x + cos(ray_angle) * offset, // !! change len white a var
			player.y + sin(ray_angle) * offset
		),
		BLUE
	) ;
	draw_line(line, player.img);
	return ray;
}

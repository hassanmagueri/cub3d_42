/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:56:00 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/10 13:12:11 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#include "MLX/MLX42.h"
#include <math.h>


int	draw_react_minimap(t_rect rect, mlx_image_t *image, int width, int height)
{
	double i;
	double j;
	// do border_with;

	// border_with = 0;
	i = rect.y;
	while (i <= rect.y + height)
	{
		j = rect.x;
		while (j <= rect.x + width)
		{
			if (j >= 0 && i >= 0 && j <= image->width && i <= image->height)
				mlx_put_pixel(image, j, i, rect.color);
			j++;
		}
		i++;
	}
	return (1);
}

int border_minimap(mlx_image_t *img, t_circle c)
{
		for(int i = 0; i < img->width; i++)
		for(int j = 0; j < img->width; j++)
		{
			if (
				pow(j - c.x,2) + pow(i - c.y,2) >= pow(img->width / 2 - 16, 2) &&
				pow(j - c.x,2) + pow(i - c.y,2) < pow(img->width / 2 - 8, 2)
				)
				mlx_put_pixel(img, j, i, BLACK);
			if ( pow(j - c.x,2) + pow(i - c.y,2) > pow(img->width / 2 - 8, 2))
				mlx_put_pixel(img, j, i, 0);
		}
	return 1;
}

int	set_walls(t_player player, mlx_image_t *img, t_map map)
{
	int x = player.x / TILE_SIZE - MINIMAP_WIDTH / 2;
	int y = player.y / TILE_SIZE - MINIMAP_HEIGHT / 2;
	// int y = (player.y - img->height / 2) / TILE_SIZE;

	int j = 0;
	int i = 0;

	double player_x = player.x * SCALE;
	double player_y = player.y * SCALE;
	int xn = 0;
	int yn = 0;
	if (player_x <= 5 * SCALE_SIZE)
		xn = 1;
	if (player_y <= 5 * SCALE_SIZE)
		yn = 1;
	
	while (i < MINIMAP_HEIGHT * SCALE_SIZE) 
	{
		j = 0;
		while (j < MINIMAP_WIDTH * SCALE_SIZE) 
		{
			if (pow(j - MINIMAP_WIDTH * SCALE_SIZE / 2, 2)  + pow((i - MINIMAP_HEIGHT * SCALE_SIZE / 2) , 2) < pow((MINIMAP_WIDTH / 2) * SCALE_SIZE, 2))
			{
				int player_offx_tile = player_x - ((int)(player.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE / 2) * SCALE;
				int player_offy_tile = player_y - ((int)(player.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE / 2) * SCALE;
				int i_scale = (int)((i + y * SCALE_SIZE + player_offy_tile) / SCALE_SIZE);
				int j_scale = (int)((j + x * SCALE_SIZE + player_offx_tile) / SCALE_SIZE);
				if (i_scale - yn < 0 || j_scale - xn < 0 || i_scale >= map.height || j_scale >= map.width)
					mlx_put_pixel(img, j, i , SEMI_BLACK);
				else
				 if (map.layout[i_scale - yn][j_scale - xn] == '1')
					mlx_put_pixel(img, j, i , GREY);
				
			}
			j++;
		}
		i++;
	}
	return 1;
}

int set_rays(t_player player, mlx_image_t *img, t_map map, t_ray rays[NUM_RAYS])
{
	// t_ray *rays = rays_param;
	int i = 0;
	int x = (img->width - img->width / 2);
	int y = (img->height - img->height / 2);
	while (i < NUM_RAYS)
	{
		draw_line(
			new_line(
				(t_point){x,y},
				(t_point){rays[i].dx * SCALE + x, (rays[i].dy * SCALE + y)},
				YELLOW),
				img
		);	
		i++;
	}
	return 1;
}

int draw_minimap(t_data *data)
{
	mlx_image_t *img;
	t_player	player;

	player = data->player;
	img = data->minimap_img;
	
	// img = mlx_new_image(data->mlx, TILE_SIZE * SCALE * MINIMAP_WIDTH, TILE_SIZE * SCALE * MINIMAP_HEIGHT);
	// mlx_image_to_window(data->mlx, img, 0,200);
	// img = new_image_to_window(data->mlx, TILE_SIZE * SCALE * 10, TILE_SIZE * SCALE * 10);
	t_circle c = new_circle(img->width/2, img->height/2, player.radius, SEMI_LIME);
	for(int i = 0; i < img->width; i++)
		for(int j = 0; j < img->width; j++)
			if (pow(j - c.x,2) + pow(i - c.y,2) < pow(img->width / 2, 2))
				mlx_put_pixel(img, j, i, SEMI_WHITE);
	draw_circle(c, img);
	set_walls(player, img, data->map);
	t_line line = new_line(
			new_point(img->width / 2, img->height/ 2),
			new_point(
				(img->width / 2 + (cos(player.angle) * 100 * SCALE_SIZE) * SCALE),
				(img->height / 2 + (sin(player.angle) * 100 * SCALE_SIZE) * SCALE)
			)
			, RED
		);
	draw_line(line, img);
	// set_rays(player, img, data->map, (data->rays));
	
	border_minimap(img, c);
	return 1;
}


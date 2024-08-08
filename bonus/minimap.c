/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:56:00 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/08 18:03:20 by emagueri         ###   ########.fr       */
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

int border_minimap(mlx_image_t *img)
{
	int i = 0;
	while(i < img->width)
	{
		mlx_put_pixel(img, 0, i, RED);
		mlx_put_pixel(img, i, 0, RED);
		mlx_put_pixel(img, img->width - 1, i, RED);
		mlx_put_pixel(img, i, img->height - 1, RED);
		i++;
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
	while (i <= MINIMAP_HEIGHT) 
	{
		j = 0;
		while (j <= MINIMAP_WIDTH) 
		{
			int player_offx_tile = player_x - ((int)(player.x / TILE_SIZE ) * TILE_SIZE + TILE_SIZE / 2) * SCALE;
			int player_offy_tile = player_y - ((int)(player.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE / 2) * SCALE;
			// printf("x: {%f}\n", j * SCALE_SIZE - player_offx_tile);
			if (y + i >= map.height || x + j - xn > map.width || x + j - xn < 0 || y + i - yn < 0)
				draw_react_minimap(
							new_rect(j * SCALE_SIZE - player_offx_tile, i * SCALE_SIZE - player_offy_tile, 0,SEMI_WHITE),
							img, SCALE_SIZE, SCALE_SIZE);
			else if (map.layout[y + i - yn][x + j - xn] == '1')
					draw_react_minimap(
								new_rect(j * SCALE_SIZE - player_offx_tile, i * SCALE_SIZE - player_offy_tile, 0,SEMI_GREY),
								img, SCALE_SIZE, SCALE_SIZE);
			j++;
		}
		// printf("--------------\n");
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
				SEMI_LIME),
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
	for(int i = 0; i < img->width; i++)
		for(int j = 0; j < img->width; j++)
			mlx_put_pixel(img, j, i, SEMI_WHITE);
	t_circle c = new_circle(img->width/2, img->height/2, player.radius, SEMI_LIME);
	draw_circle(c, img);
	
	border_minimap(img);
	set_walls(player, img, data->map);
	set_rays(player, img, data->map, (data->rays));
	return 1;
}


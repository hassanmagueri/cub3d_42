/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:56:00 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/07 09:48:44 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#include "MLX/MLX42.h"

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
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (y > MINIMAP_HEIGHT)
		y = MINIMAP_HEIGHT - 1;
	if (x > MINIMAP_WIDTH)
		x = MINIMAP_WIDTH - 1;
	printf("player.x : %f\n", player.x / TILE_SIZE);
	// printf("x : %d\n", x);
	// printf("y : %d\n", y);
	while (i < MINIMAP_HEIGHT) 
	{
		j = 0;
		while (j < MINIMAP_WIDTH) 
		{
			if (map.layout[y + i][x + j] == '1')
				draw_react(new_rect(j * TILE_SIZE * SCALE, i * TILE_SIZE * SCALE, TILE_SIZE * SCALE, YELLOW), img);
			printf("x : %f\n", j * TILE_SIZE * SCALE);
			printf("y : %f\n", i * TILE_SIZE * SCALE);
			printf("%c\n",map.layout[y + i][x + j]);
			j++;
		}
		i++;
	}
	return 1;
}

int draw_minimap(t_data *data)
{
	mlx_image_t *img;
	t_player	player;

	player = data->player;
	img = mlx_new_image(data->mlx, TILE_SIZE * SCALE * 10, TILE_SIZE * SCALE * 10);
	mlx_image_to_window(data->mlx, img, 0,200);
	// img = new_image_to_window(data->mlx, TILE_SIZE * SCALE * 10, TILE_SIZE * SCALE * 10);
	for(int i = 0; i < img->width; i++)
		for(int j = 0; j < img->width; j++)
			mlx_put_pixel(img, j, i, BLACK);
	t_circle c = new_circle(img->width/2, img->height/2, player.radius, LIME);
	draw_circle(c, img);
	
	border_minimap(img);
	set_walls(player, img, data->map);
	
	return 1;
}


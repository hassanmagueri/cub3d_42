/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/13 16:55:04 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// void ft_

void	ft_hook(void *param)
{
	t_data *data = param;
	t_player player;

	player = data->player;
	// player = data->player.img;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		// player->instances[0].y -= 1;
		data->player.walk_direction = 1;
		update_player(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		// player->instances[0].y += 1;
		data->player.walk_direction = -1;
		update_player(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		// player->instances[0].y += 1;
		data->player.rotation_angle = degtorad(1);
		update_player(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		// player->instances[0].y += degtorad(1);
		data->player.rotation_angle = degtorad(-1);
		printf("asd\n");
		update_player(data);
	}
	// 	player->instances[0].x -= 1;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	// 	player->instances[0].x += 1;
}

int render_map(t_data *data)
{
	int i, j;
	i = 0;

	t_point p;
	int x, y;
	int radius = 8;
	p.x = 0;
	p.y = 0;
	p.width = TILE_SIZE;
	p.height = TILE_SIZE;
	mlx_image_t *rect_img = mlx_new_image(data->mlx, TILE_SIZE * 20,TILE_SIZE * 20);
	data->player = new_player(data);
	mlx_image_t *player_img = data->player.img;
	data->player.img = player_img;
	while (i < 12)
	{
		j = 0;
		while (j < 14)
		{
			if (data->grid[i][j] == '1')
			{
				t_rect r = new_rect(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, 0xFFFFFFFF);
				draw_react(r, rect_img);
			}
			if (data->grid[i][j] == 'P')
			{
				x = (j * TILE_SIZE) + TILE_SIZE / 2 - (player_img->width / 2) + radius;
				y = (i * TILE_SIZE) + TILE_SIZE / 2 - (player_img->height / 2) + radius;
			}
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, rect_img,0, 0);
	draw_player(data, new_point(x, y));
	return (1);
}


int32_t main(void)
{
	t_data data;
	char grid[][14] = {
		"11111111111111",
		"10110001111111",
		"10110001010011",
		"10110001010011",
		"10110101010011",
		"10110001010011",
		"10110001010011",
		"10110101010111",
		"10110001011P11",
		"10110101010111",
		"10110101010011",
		"11111111111111"
		};
	data.mlx = mlx_init(WIDTH * 2, HEIGHT * 2, "cub3D", false);
	data.grid = grid;
	render_map(&data);
	// mlx_image_t *img = draw_line(&data, new_point(0, 0), new_point(100, 100), 0xB54E1AFF);
	// mlx_image_to_window(data.mlx, img, data.player.x, data.player.y);
	
	mlx_loop_hook(data.mlx, ft_hook, &data);

	// mlx_image_t *img = mlx_new_image(data.mlx, 80,80);
	// draw_line(data.mlx, new_point(0, 0), new_point(45, 5), 0XFFFFFFFF, img);
	// mlx_image_to_window(data.mlx, img, 64,64);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}

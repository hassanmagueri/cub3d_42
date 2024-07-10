/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/10 10:28:13 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_hook(void *param)
{
	t_data *mlx = param;
	mlx_image_t *player;

	player = mlx->player.img;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx->mlx);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_UP))
		player->instances[0].y -= 5;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_DOWN))
		player->instances[0].y += 5;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
		player->instances[0].x -= 5;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
		player->instances[0].x += 5;
}

int render_map(t_data *data)
{
	int i, j;
	i = 0;

	t_point p;
	int x, y;
	p.x = 0;
	p.y = 0;
	p.width = TILE_SIZE;
	p.height = TILE_SIZE;
	mlx_image_t *rect = draw_react(data, p, 0xFFFFFFFF);
	mlx_image_t *player_img = draw_circle(data, 5, 0xFF0000FF);
	data->player.img = player_img;
	while (i < 12)
	{
		j = 0;
		while (j < 14)
		{
			if (data->grid[i][j] == '1')
				mlx_image_to_window(data->mlx, rect, j * TILE_SIZE, i * TILE_SIZE);
			if (data->grid[i][j] == 'P')
			{
				x = (j * TILE_SIZE) + TILE_SIZE / 2 - (player_img->width / 2);
				y = (i * TILE_SIZE) + TILE_SIZE / 2 - (player_img->height / 2);
			}
			j++;
		}
		i++;
	}
	new_player(data, new_point(x, y), player_img);
	mlx_image_to_window(data->mlx, player_img, x, y);
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
		"10110101010011",
		"10110001010P11",
		"10110101010011",
		"10110101010011",
		"11111111111111"};
	data.mlx = mlx_init(WIDTH * 2, HEIGHT * 2, "cub3D", false);
	data.grid = grid;
	render_map(&data);
	mlx_image_t *img = draw_line(&data, new_point(0, 0), new_point(731, 559), 0xFF0000FF);
	mlx_image_to_window(data.mlx, img, 0, 0);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}

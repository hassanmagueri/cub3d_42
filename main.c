/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/09 12:41:00 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void ft_hook(void *param)
{
	t_mlx *mlx = param;
	mlx_image_t *player;

	player = mlx->player;
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

int render_map(t_mlx *mlx)
{
	int i, j;
	i = 0;

	t_point p;
	p.x = 0;
	p.y = 0;
	p.width = TILE_SIZE;
	p.height = TILE_SIZE;
	mlx_image_t *rect = draw_react(mlx, p, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF));
	mlx_image_t *player = draw_circle(mlx, 12, 0xFF0000FF);
	mlx->player = player;
	while (i < 12)
	{
		j = 0;
		while (j < 14)
		{
			if (mlx->grid[i][j] == '1')
				mlx_image_to_window(mlx->mlx, rect, j * TILE_SIZE, i * TILE_SIZE);
			if (mlx->grid[i][j] == 'P')
			{
				int x, y;
				x = (j * TILE_SIZE) + TILE_SIZE / 2 - (player->width / 2);
				y = (i * TILE_SIZE) + TILE_SIZE / 2 - (player->height / 2);
				mlx_image_to_window(mlx->mlx, player, x, y);
			}
			j++;
		}
		i++;
	}
	return (1);
}


int32_t main(void)
{
	t_mlx mlx;
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
	mlx.mlx = mlx_init(WIDTH * 2, HEIGHT * 2, "cub3D", false);
	mlx.grid = grid;
	render_map(&mlx);

	mlx_loop_hook(mlx.mlx, ft_hook, &mlx);
	mlx_loop(mlx.mlx);
	mlx_terminate(mlx.mlx);
	return (EXIT_SUCCESS);
}

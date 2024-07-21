/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/21 12:25:09 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	get_digits(int n)
{
	size_t	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	char		*str_num;
	size_t		digits;
	long int	num;

	num = n;
	digits = get_digits(n);
	if (n < 0)
	{
		num *= -1;
		digits++;
	}
	if (!(str_num = (char *)malloc(sizeof(char) * (digits + 1))))
		return (NULL);
	*(str_num + digits) = 0;
	while (digits--)
	{
		*(str_num + digits) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(str_num + 0) = '-';
	return (str_num);
}

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
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) || mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->player.walk_direction = 1;
		update_player(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->player.walk_direction = -1;
		update_player(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player.walk_direction = -2;
		update_player(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player.walk_direction = 2;
		update_player(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.rotation_angle = degtorad(1);
		update_player(data);
		
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.rotation_angle = degtorad(-1);
		update_player(data);
	}
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
	mlx_image_t *map_img = mlx_new_image(data->mlx, TILE_SIZE * 20,TILE_SIZE * 20);
	mlx_image_t *player_img = data->player.img;
	data->player.img = player_img;
	mlx_image_to_window(data->mlx, map_img,0, 0);
	while (i < 12)
	{
		j = 0;
		while (j < 14)
		{
			if (data->grid[i][j] == '1')
			{
				t_rect r = new_rect(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, LIGHT_GREY);
				draw_react(r, map_img);
				if (i == 0)
					mlx_put_string(data->mlx, ft_itoa(j * TILE_SIZE), i * TILE_SIZE + TILE_SIZE / 4, j * TILE_SIZE + TILE_SIZE / 4);
				if (j == 0)
					mlx_put_string(data->mlx, ft_itoa(i * TILE_SIZE), i * TILE_SIZE + TILE_SIZE / 4, j * TILE_SIZE + TILE_SIZE / 4);
			}
			if (data->grid[i][j] == 'P')
			{
				x = j * TILE_SIZE + TILE_SIZE / 2;
				// 
				y = i * TILE_SIZE + TILE_SIZE / 2;
			}
			j++;
		}
		i++;
	}
	data->player = new_player(data, x, y);
	mlx_image_to_window(data->mlx, data->player.img, 0, 0);
	// draw_player(data);
	// cast_rays(NULL, data);
	update_player(data);
	return (1); 
}

int32_t	main(void)
{
	t_data data;
	char grid[][14] = {
		"11111111111111",
		"10110001111111",
		"10110001010011",
		"10110000010001",
		"10110101000011",
		"10010000000001",
		"10001000010011",
		"10000100000101",
		"10010001011011",
		"101101P1000111",
		"10000101000011",
		"11111111111111"
		};
	data.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	data.grid = grid;
	render_map(&data);
	// mlx_image_t *img = mlx_new_image(data.mlx, 1000, 1000);
	// draw_line(
	// 	new_line(
	// 			new_point(10 , 10),
	// 			new_point(100 , 400),
	// 			CYAN
	// 		),
	// 	img
	// );
	// mlx_image_to_window(data.mlx, img, 0, 0);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}

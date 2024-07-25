/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/25 18:17:29 by emagueri         ###   ########.fr       */
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

void	ft_hook(void *param)
{
	t_data *data = param;
	t_player *player;

	player = &data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) || mlx_is_key_down(data->mlx, MLX_KEY_UP))
		player->walk_direction = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		player->walk_direction = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		player->walk_direction = -2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		player->walk_direction = 2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		player->rotation_angle = degtorad(1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		player->rotation_angle = degtorad(-1);
	if (player->rotation_angle != 0 || player->walk_direction != 0)
		update_player(data);
}

int render_map(t_data *data)
{
	mlx_image_t	*map_img;
	mlx_image_t	*player_img = data->player.img;
	int			i;
	int			j;

	i = 0;
	data->player.img = player_img;
	map_img = new_image_to_window(data->mlx, TILE_SIZE * 20, TILE_SIZE * 20);
	while (i < 12)
	{
		j = 0;
		while (j < 14)
		{
			if (data->grid[i][j] == '1')
				draw_react((t_rect){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, LIGHT_GREY}, map_img);
			if (data->grid[i][j] == 'P')
				data->player = new_player(data, j * TILE_SIZE + TILE_SIZE / 2,
					i * TILE_SIZE + TILE_SIZE / 2);
			j++;
		}
		i++;
	}
	update_player(data);
	return (1); 
}

int32_t	main(void)
{
	t_data data;
	// char grid[][14] = {
	// 	"111111",
	// 	"1P1101",
	// 	"100001",
	// 	"101101",
	// 	"111111"
	// 	};
	char grid[][14] = {
		"11111111111111",
		"10000011111111",
		"10000000101001",
		"10000001000111",
		"10000010010111",
		"100000P0000001",
		"10000000000011",
		"10000000000101",
		"10000000000001",
		"10000000000001",
		"10000000000001",
		"11111111111111"
		};
	// char grid[][14] = {
	// 	"11111111111111",
	// 	"10110001111111",
	// 	"10000100101001",
	// 	"10110010010001",
	// 	"10110101001011",
	// 	"100100P0000001",
	// 	"10000101000011",
	// 	"10000010000101",
	// 	"10010001001011",
	// 	"10100101000111",
	// 	"10000101000011",
	// 	"11111111111111"
	// 	};
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

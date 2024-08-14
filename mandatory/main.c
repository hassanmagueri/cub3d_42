/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/13 10:58:10 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX/MLX42.h"
#include "cub3d.h"

static size_t get_digits(int n)
{
	size_t i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

void ft_hook(void *param)
{
	t_data *data;
	t_player *player;

	data = param;
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
void draw_map(t_data *data, char *map, int i, mlx_image_t *map_img)
{
	int j;
	int angle;

	j = 0;
	while (j < data->map.width)
	{
		if (map[j] == '1')
			draw_react((t_rect){i * TILE_SIZE * SCALE,
								j * TILE_SIZE * SCALE, TILE_SIZE * SCALE, BLACK},
					   map_img);
		if (map[j] == 'N' || map[j] == 'S' || map[j] == 'W' || map[j] == 'E')
		{
			if (map[j] == 'N')
				angle = 270;
			else if (map[j] == 'W')
				angle = 180;
			else if (map[j] == 'S')
				angle = 90;
			else if (map[j] == 'E')
				angle = 0;
			data->player = new_player(data, j * TILE_SIZE + TILE_SIZE / 2,
									  i * TILE_SIZE + TILE_SIZE / 2, angle);
		}
		j++;
	}
}

int render_map(t_data *data)
{
	mlx_image_t *map_img;
	mlx_image_t *player_img;
	t_map map;
	int i;
	int j;

	player_img = data->player.img;
	i = 0;
	map = data->map;
	map_img = new_image_to_window(data->mlx, TILE_SIZE * SCALE * map.width,
								  TILE_SIZE * SCALE * map.height);
	while (i < map.height)
	{
		draw_map(data, map.layout[i], i, map_img);
		i++;
	}
	update_player(data);
	return (1);
}
void init_window(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	data->window_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->background_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
}
void init_texture(t_data *data)
{

	data->textures.EA = mlx_load_png(data->EA);
	data->textures.NO = mlx_load_png(data->NO);
	data->textures.SO = mlx_load_png(data->SO);
	data->textures.WE = mlx_load_png(data->WE);
}
void draw_floor_ceiling(t_data *data)
{

	int i;
	int j;

	i = 0;
	while (i < data->background_img->height / 2)
	{
		j = 0;
		while (j < data->background_img->width)
		{
			mlx_put_pixel(data->background_img, j, i, ft_pixel(data->ceiling));
			mlx_put_pixel(data->background_img, j,
					i + data->background_img->height / 2, ft_pixel(data->floor));
			j++;
		}
		i++;
	}
}
int32_t main(int ac, char const **av)
{
	t_data data;
	load_map_data(&data);
	validate_top_map(&data);
	set_map(&data);
	validate_all_dirs(&data);
	validate_colors(&data);
	parse_map(&data);
	init_clrs_dirs(&data);
	init_window(&data);
	init_texture(&data);
	draw_floor_ceiling(&data);
	mlx_image_to_window(data.mlx, data.background_img, 0, 0);
	mlx_image_to_window(data.mlx, data.window_img, 0, 0);
	render_map(&data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}

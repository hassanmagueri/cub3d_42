/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/25 00:16:37 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX/MLX42.h"
#include "cub3d.h"

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
	size_t j;
	size_t angle;

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
	size_t i;

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
	if (!data->textures.EA)
		ft_putendl_fd_color("Error\nInvalid texture path", 2, RED_E);
	data->textures.NO = mlx_load_png(data->NO);
	if (!data->textures.NO)
		ft_putendl_fd_color("Error\nInvalid texture path", 2, RED_E);
	data->textures.SO = mlx_load_png(data->SO);
	if (!data->textures.SO)
		ft_putendl_fd_color("Error\nInvalid texture path", 2, RED_E);
	data->textures.WE = mlx_load_png(data->WE);
	if (!data->textures.WE)
		ft_putendl_fd_color("Error\nInvalid texture path", 2, RED_E);
}
void draw_floor_ceiling(t_data *data)
{

	size_t i;
	size_t j;

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
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *str1;
	unsigned char *str2;
	size_t i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && (str1[i] == str2[i]) && i < n - 1)
		i++;
	return (str1[i] - str2[i]);
}
void check_extension(char const *file)
{
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
		ft_putendl_fd_color("Error\nInvalid file extension", 2, RED_E);
}
int32_t main(int ac, char const **av)
{

	t_data data;
	if (ac != 2)
		ft_putendl_fd_color("Error\nInvalid number of arguments", 2, RED_E);
	check_extension(av[1]);
	data.map_path = ft_strdup(av[1]);
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

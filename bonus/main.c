/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/10 12:53:37 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_data *data = param;
	t_player *player;

	player = &data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_O))
	{
		if (data->x_door != -1 && data->y_door != -1)
		{
			int player_tile_x = (int)(data->player.x / TILE_SIZE) + data->place_x;
			int player_tile_y = (int)(data->player.y / TILE_SIZE) + data->place_y;
			char current_tile = data->map.layout[player_tile_y][player_tile_x];
			if (current_tile == 'C' || current_tile == 'O')
			{
				data->map.layout[data->y_door][data->x_door] = 'O';
				data->y_door = -1;
				data->x_door = -1;
				update_player(data);
			}
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_C))
	{
		if (data->x_door != -1 && data->y_door != -1)
		{
			int player_tile_x = (int)(data->player.x / TILE_SIZE) + data->place_x;
			int player_tile_y = (int)(data->player.y / TILE_SIZE) + data->place_y;

			char current_tile = data->map.layout[player_tile_y][player_tile_x];

			if (current_tile == 'C' || current_tile == 'O')
			{
				data->map.layout[data->y_door][data->x_door] = 'C';
				data->x_door = -1;
				data->y_door = -1;
				update_player(data);
			}
		}
	}

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
	mlx_image_t *map_img;
	mlx_image_t *player_img = data->player.img;
	t_map map;
	int i;
	int j;

	i = 0;
	map = data->map;
	map_img = new_image_to_window(data->mlx, TILE_SIZE * SCALE * map.width, TILE_SIZE * SCALE * map.height);
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (map.layout[i][j] == '1')
				draw_react((t_rect){i * TILE_SIZE * SCALE, j * TILE_SIZE * SCALE, TILE_SIZE * SCALE, BLACK}, map_img);
			if (map.layout[i][j] == 'N' || map.layout[i][j] == 'S' || map.layout[i][j] == 'W' || map.layout[i][j] == 'E')
			{
				int angle;
				if (map.layout[i][j] == 'N')
					angle = 270;
				else if (map.layout[i][j] == 'W')
					angle = 180;
				else if (map.layout[i][j] == 'S')
					angle = 90;
				else if (map.layout[i][j] == 'E')
					angle = 0;
				data->player = new_player(data, j * TILE_SIZE + TILE_SIZE / 2,
										  i * TILE_SIZE + TILE_SIZE / 2, angle);
			}
			j++;
		}

		i++;
	}
	update_player(data);
	return (1);
}
void ft_put_image(t_data *data, mlx_image_t *img)
{
	mlx_image_to_window(data->mlx, img, 300, 300);
}
void ft_strcpy(char *dest, char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}
void ft_strcut(char *dest, char *src)
{
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}
void animation_sprite(void *arg)
{
	t_data *data = (t_data *)arg;
	static int i;
	static bool is_pressed;
	static mlx_image_t *remove_img = NULL;

	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	{
		mlx_delete_image(data->mlx, data->default_img);
		data->default_img = mlx_texture_to_image(data->mlx, data->tex_plr);
		is_pressed = true;
	}
	if (is_pressed)
	{
		if (remove_img)
			mlx_delete_image(data->mlx, remove_img);
		if (i < NUM_IMAGES)
		{
			char path[100] = "./sprite_gun/StechkinEx";
			char index[10];
			char png[10];
			ft_strcpy(index, ft_itoa(i + 1));
			ft_strcpy(png, ".png");
			ft_strcut(path, index);
			ft_strcut(path, png);
			mlx_texture_t *txr = mlx_load_png(path);
			data->spr_img = mlx_texture_to_image(data->mlx, txr);
			remove_img = data->spr_img;
			ft_put_image(data, data->spr_img);
			mlx_delete_texture(txr);

			i++;
		}
		if (i == NUM_IMAGES)
		{
			i = 0;
			mlx_delete_image(data->mlx, data->spr_img);
			mlx_image_to_window(data->mlx, data->default_img, 300, 300);
			is_pressed = false;
		}
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
	// data.map = data.map_data;
	int i = 0;
	data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	data.texture = mlx_load_png("./images/test.png");
	// printf("images path: %s\n", data.SO);
	data.textures.EA = mlx_load_png(data.EA);
	data.textures.NO = mlx_load_png(data.NO);
	data.textures.SO = mlx_load_png(data.SO);
	data.textures.WE = mlx_load_png(data.WE);
	data.wall_door = 'C';
	data.x_door = -1;
	data.y_door = -1;
	// printf("width: %d\n", data.textures.NO->width);
	data.window_img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.background_img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	for (int i = 0; i < data.background_img->height / 2; i++)
	{
		for (int j = 0; j < data.background_img->width; j++)
		{
			mlx_put_pixel(data.background_img, j, i, ft_pixel(data.ceiling));
			mlx_put_pixel(data.background_img, j, i + data.background_img->height / 2, ft_pixel(data.floor));
		}
	}
	mlx_image_to_window(data.mlx, data.background_img, 0, 0);
	mlx_image_to_window(data.mlx, data.window_img, 0, 0);
	// data.texture=mlx_load_png("./images/wall_1024.png");
	data.tex_plr = mlx_load_png("./sprite_gun/Stechkin01.png");
	data.tex_door = mlx_load_png("./images/door_close.png");

	data.default_img = mlx_texture_to_image(data.mlx, data.tex_plr);
	mlx_image_to_window(data.mlx, data.default_img, 300, 300);
	mlx_loop_hook(data.mlx, animation_sprite, &data);
	render_map(&data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}

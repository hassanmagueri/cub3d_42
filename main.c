/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/06 17:50:01 by belguabd         ###   ########.fr       */
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
	map_img = new_image_to_window(data->mlx, TILE_SIZE * map.width, TILE_SIZE * map.height);
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (map.layout[i][j] == '1')
				draw_react((t_rect){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, LIGHT_GREY}, map_img);
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
void animation_sprite(void *arg)
{
	t_data *data = (t_data *)arg;
	mlx_image_to_window(data->mlx, data->img_spt[0], 400, 450);
}

// char *ft_str_join_three(char *path, int index, char *png)
// {
// }

void ft_strcpy(char *dest, char *src)
{
	int i;
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void ft_strcut(char *dest, char *src)
{
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}
void load_images(t_data *data)
{

	int i = 0;
	
	while (i < NUM_IMAGES)
	{
		char path[100] = "./sprite_gun/StechkinEx";
		char index[10];
		char png[10];
		ft_strcpy(index, ft_itoa(i + 1));
		ft_strcpy(png, ".png");
		ft_strcut(path, index);
		ft_strcut(path, png);
		data->txr_spt[i] = mlx_load_png(path);
		data->img_spt[i] = mlx_texture_to_image(data->mlx, data->txr_spt[i]);
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
	// data.map = data.map_data;
	int i=0;
	data.mlx = mlx_init(WINDOW_WIDTH , WINDOW_HEIGHT, "cub3D", false);
	data.texture=mlx_load_png("./images/test.png");
	printf("images path: %s\n", data.SO);
	data.textures.EA = mlx_load_png(data.EA);
	data.textures.NO = mlx_load_png(data.NO);
	data.textures.SO = mlx_load_png(data.SO);
	data.textures.WE = mlx_load_png(data.WE);
	printf("width: %d\n", data.textures.NO->width);
	// data.texture=mlx_load_png("./images/wall_1024.png");
	data.window_img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	render_map(&data);
	mlx_loop_hook(data.mlx, animation_sprite, &data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}

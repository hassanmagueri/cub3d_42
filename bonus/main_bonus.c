/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/24 17:17:34 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX/MLX42.h"
#include "cub3d_bonus.h"
#define NUM_IMAGES 68
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
	t_map map = data->map;
	t_player *player;

	player = &data->player;
	doors(data, map);
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



void move_mouse(double x_pos, double y_pos, void *arg)
{
	t_data *data = (t_data *)arg;
	double delta_x = x_pos - (WINDOW_WIDTH / 2);
	data->player.rotation_angle += delta_x * 0.0001;
	mlx_set_mouse_pos(data->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void parsing_part(t_data *data)
{
	load_map_data(data);
	validate_top_map(data);
	set_map(data);
	validate_all_dirs(data);
	validate_colors(data);
	parse_map(data);
	init_clrs_dirs(data);
	parsing_doors(data);
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
void f(){
	system("leaks cub3D_bonus");
}
int32_t main(int ac, char const **av)
{

	t_data data;
	if (ac != 2)
		ft_putendl_fd_color("Error\nInvalid number of arguments", 2, RED_E);
	check_extension(av[1]);
	data.map_path = ft_strdup(av[1]);
	parsing_part(&data);
	int x = 0;
	while (data.map.layout[x])
	{
		printf("%s\n", data.map.layout[x]);
		x++;
	}
	int i = 0;
	data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D_bonus", false);
	data.textures.EA = mlx_load_png(data.EA);
	data.textures.NO = mlx_load_png(data.NO);
	data.textures.SO = mlx_load_png(data.SO);
	data.textures.WE = mlx_load_png(data.WE);
	data.wall_door = 'C';
	data.window_img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.background_img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.minimap.img = mlx_new_image(data.mlx, MINIMAP_HEIGHT * SCALE_SIZE, MINIMAP_WIDTH * SCALE_SIZE);
	for (int i = 0; i < data.background_img->height / 2; i++)
		for (int j = 0; j < data.background_img->width; j++)
		{
			mlx_put_pixel(data.background_img, j, i, ft_pixel(data.ceiling));
			mlx_put_pixel(data.background_img, j, i + data.background_img->height / 2, ft_pixel(data.floor));
		}
	mlx_image_to_window(data.mlx, data.background_img, 0, 0);
	mlx_image_to_window(data.mlx, data.window_img, 0, 0);
	mlx_image_to_window(data.mlx, data.minimap.img, 0, 0);
	data.tex_plr = mlx_load_png("./sprite/Stechkin01.png");
	data.tex_door = mlx_load_png("./images/door_close.png");
	data.default_img = mlx_texture_to_image(data.mlx, data.tex_plr);
	mlx_image_to_window(data.mlx, data.default_img, 300, 300);
	mlx_loop_hook(data.mlx, animation_sprite, &data);
	render_map(&data);
	mlx_cursor_hook(data.mlx, move_mouse, &data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_DISABLED);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_malloc(FREE, FREE);
}

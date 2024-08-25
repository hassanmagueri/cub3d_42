/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/25 04:47:16 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

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

void set_player_direction(t_data *data, t_index index)
{
	t_map	map;
	int		angle;
	int		i;
	int		j;

	i = index.i;
	j = index.j;
	map = data->map;
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

int render_map(t_data *data)
{
	t_map	map;
	int		i;
	int		j;

	i = 0;
	map = data->map;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (map.layout[i][j] == 'N' || map.layout[i][j] == 'S'
				|| map.layout[i][j] == 'W' || map.layout[i][j] == 'E')
			{
				set_player_direction(data, (t_index){i, j});
				return (update_player(data), 1);
			}
			j++;
		}
		i++;
	}
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

int painting_background(mlx_image_t *img, t_clr ceiling, t_clr floor)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->height / 2)
	{
		j = 0;
		while (j < img->width)
		{
			mlx_put_pixel(img, j, i, ft_pixel(ceiling));
			mlx_put_pixel(img, j, i + img->height / 2, ft_pixel(floor));
			j++;
		}
		i++;
	}
	return 0;
}

void delete_image(mlx_t *mlx, mlx_image_t *img)
{
	if (img)
		mlx_delete_image(mlx, img);
}

void delete_texture(mlx_texture_t *texture)
{
	if (texture)
		mlx_delete_texture(texture);
}

void	terminate_mlx(t_data *data)
{
	delete_texture(data->tex);
	delete_texture(data->tex_door);
	delete_texture(data->texture);
	delete_texture(data->tex_plr);
	delete_texture(data->textures.EA);
	delete_texture(data->textures.NO);
	delete_texture(data->textures.SO);
	delete_texture(data->textures.WE);
	delete_image(data->mlx, data->minimap.img);
	delete_image(data->mlx, data->background_img);
	delete_image(data->mlx, data->img);
	delete_image(data->mlx, data->spr_img);
	delete_image(data->mlx, data->spr_img);
	delete_image(data->mlx, data->window_img);
	mlx_terminate(data->mlx);
	exit(1);
}

void set_mlx_vars_null(t_data *data)
{
	data->minimap.img		= NULL;
	data->background_img	= NULL;
	data->default_img		= NULL;
	data->img				= NULL;
	data->spr_img			= NULL;
	data->tex				= NULL;
	data->tex_door			= NULL;
	data->texture			= NULL;
	data->tex_plr			= NULL;
	data->textures			= (t_textures){NULL, NULL, NULL, NULL};
	data->window_img		= NULL;
}

mlx_texture_t*	load_png(t_data *data, char *path)
{
	mlx_texture_t* texture;

	texture = mlx_load_png(path);
	if (texture == NULL)
		terminate_mlx(data);
	return (texture);
}

mlx_image_t*	new_image(t_data *data, int width, int height)
{
	mlx_image_t*	img;

	img = mlx_new_image(data->mlx, width, height);
	if (img == NULL)
		terminate_mlx(data);
	return (img);
}

mlx_image_t*	texture_to_image(t_data *data, mlx_texture_t *texture)
{
	mlx_image_t*	img;

	if (texture == NULL)
		terminate_mlx(data);
	img = mlx_texture_to_image(data->mlx, texture);
	if (img == NULL)
		terminate_mlx(data);
	return (img);
}

void	init_vars(t_data *data)
{
	set_mlx_vars_null(data);

	data->textures.EA	= load_png(data, data->EA);
	data->textures.NO	= load_png(data, data->NO);
	data->textures.SO	= load_png(data, data->SO);
	data->textures.WE	= load_png(data, data->WE);
	data->tex_door		= load_png(data, "./images/door_close.png");
	data->window_img	= new_image(data, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->background_img= new_image(data, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->minimap.img	= new_image(data, MINIMAP_HEIGHT * SCALE_SIZE, MINIMAP_WIDTH * SCALE_SIZE);
	data->tex_plr		= load_png(data, "./sprite/Stechkin01.png");
	data->default_img	= texture_to_image(data, data->tex_plr);
}

void	image_to_window(t_data *data, mlx_image_t *img, int x, int y)
{
	int res;

	res = mlx_image_to_window(data->mlx, img, x, y);
	if (res == -1)
		terminate_mlx(data);
}

int32_t main(int ac, char const **av)
{
	t_data	data;

	if (ac != 2)
		ft_putendl_fd_color("Error\nInvalid number of arguments", 2, RED_E);
	check_extension(av[1]);
	data.map_path = ft_strdup(av[1]);
	parsing_part(&data);
	int i = 0;
	data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D_bonus", false);

	init_vars(&data);

	image_to_window(&data, data.background_img, 0, 0);
	image_to_window(&data, data.window_img, 0, 0);
	image_to_window(&data, data.minimap.img, 0, 0);
	image_to_window(&data, data.default_img, 300, 300);
	
	painting_background(data.background_img, data.ceiling, data.floor);
	render_map(&data);
	mlx_loop_hook(data.mlx, animation_sprite, &data);
	mlx_cursor_hook(data.mlx, move_mouse, &data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_DISABLED);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	// ft_malloc(FREE, FREE);
}

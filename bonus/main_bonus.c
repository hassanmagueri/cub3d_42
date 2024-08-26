/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/26 03:07:41 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

#define NUM_IMAGES 68

size_t	get_digits(int n)
{
	size_t	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

void	ft_hook(void *param)
{
	t_data		*data;
	t_map		map;
	t_player	*player;

	data = (t_data *)param;
	map = data->map;
	player = &data->player;
	doors(data, map);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		player->walk_direction = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
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

void	set_player_direction(t_data *data, t_index index)
{
	t_map	map;
	int		angle;
	int		i;
	int		j;

	angle = 0;
	map = data->map;
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

int	render_map(t_data *data)
{
	t_map	map;
	size_t	i;
	size_t	j;

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

void	move_mouse(double x_pos, double y_pos, void *arg)
{
	t_data	*data;
	double	delta_x;

	(void) y_pos;
	data = (t_data *)arg;
	delta_x = x_pos - (WINDOW_WIDTH / 2);
	data->player.rotation_angle += delta_x * 0.0001;
	mlx_set_mouse_pos(data->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void	parsing_part(t_data *data)
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && (str1[i] == str2[i]) && i < n - 1)
		i++;
	return (str1[i] - str2[i]);
}

void	check_extension(char const *file)
{
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
		ft_putendl_fd_color("Error\nInvalid file extension", 2, RED_E);
}

int	painting_background(mlx_image_t *img, t_clr ceiling, t_clr floor)
{
	size_t	i;
	size_t	j;

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
	return (0);
}
void f(){system("leaks cub3D_bonus");}
int	main(int ac, char const **av)
{
	t_data	data;

	atexit(f);
	if (ac != 2)
		ft_putendl_fd_color("Error\nInvalid number of arguments", 2, RED_E);
	check_extension(av[1]);
	data.map_path = ft_strdup(av[1]);
	parsing_part(&data);
	data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D_bonus", false);
	if (data.mlx == NULL)
		return (ft_malloc(FREE,FREE), EXIT_FAILURE);
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
	terminate_mlx(&data);
}

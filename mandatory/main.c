/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:50 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/28 13:07:40 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	ft_hook(void *param)
{
	t_data		*data;
	t_player	*player;

	data = param;
	player = &data->player;
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

int	render_map(t_data *data)
{
	t_map	map;
	size_t	i;

	i = 0;
	map = data->map;
	while (i < map.height)
	{
		set_player(data, map.layout[i], i);
		i++;
	}
	update_player(data);
	return (1);
}

void	check_extension(char const *file)
{
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
		ft_putendl_fd_color("Error\nInvalid file extension", 2, RED_E);
}

void	f(void)
{
	system("leaks cub3D");
}

int32_t	main(int ac, char const **av)
{
	t_data	data;

	atexit(f);
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
	data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "CUB_3D", false);
	if (data.mlx == NULL)
		return (EXIT_FAILURE); // expetead leaks
	init_vars(&data);
	draw_floor_ceiling(&data);
	image_to_window(&data, data.background_img, 0, 0);
	image_to_window(&data, data.window_img, 0, 0);
	render_map(&data);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	terminate_mlx(&data);
}

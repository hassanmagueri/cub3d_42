/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:51:11 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/03 21:52:23 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double degtorad(int deg)
{
	return deg * (M_PI / 180);
}

double radtodeg(double rad)
{
	return rad * (180 / M_PI);
}

int low(int n1, int n2)
{
	if (n2 < n1)
		n1 = n2;
	return n1;
}

int xtoj(int x)
{
	int j = x / TILE_SIZE;
	return (x / TILE_SIZE);
}
int ytoi(int y)
{
	int i = y / TILE_SIZE;
	return (y / TILE_SIZE);
}

t_player new_player(t_data *data, int x, int y)
{
	t_player player;

	player.img = new_image_to_window(data->mlx, TILE_SIZE * data->map.width, TILE_SIZE * data->map.height);
	player.x = x;
	player.y = y;
	player.angle = degtorad(DEG);
	player.rotation_angle = 0;
	player.rotation_speed = 3;
	player.walk_direction = 0;
	player.move_speed = 3;
	player.radius = P_RAD;
	data->player = player;
	return player;
}

int create_vector_player(t_data *data)
{
	t_player player = data->player;
	t_point p2;
	t_line line;

	p2 = new_point(
		data->player.x + (cos(player.angle) * player.radius),
		data->player.y + (sin(player.angle) * player.radius)
	);
	line = new_line(
			new_point(player.x, player.y),
			new_point(
				data->player.x + (cos(player.angle) * player.radius),
				data->player.y + (sin(player.angle) * player.radius)
			)
			, 0xFFFF00FF
		);
	draw_line(line, data->player.img);
	return (1);
}

int draw_player(t_data *data)
{
	mlx_image_t	*img;
	int			radius;
	t_player	player;

	player = data->player;
	radius = 8;
	img = data->player.img;
	t_circle c = new_circle(player.x, player.y, player.radius, 0xFF0000FF);
	draw_circle(c, img);
	create_vector_player(data);
	// mlx_image_to_window(data->mlx, img, 0, 0);
	data->player_img = img;
	return (1);
}

mlx_image_t	*reset_img(t_data *data)
{
	// mlx_delete_image(data->mlx, data->player.img);
	// return mlx_new_image(data->mlx, WIDTH, HEIGHT);
	size_t i;
	for (i = 0; i  < data->player.img->width; i++)
	{
		size_t j;
		for (j = 0; j < data->player.img->height; j++)
			mlx_put_pixel(data->player.img, i, j, 0);
	}
	return data->player.img;
}

// t_point translate_to_index(t_point p)
// {
// 	t_point res;

	
// }

// bool is_wall(char **map, int x, int y)
bool	is_wall(t_data *data, int x, int y)
{
	int	i;
	int	j;

	char	**map;

	map = data->map.layout;
	i = y / TILE_SIZE;
	j = x / TILE_SIZE;
	if (i < 0 || j < 0 || i >= data->map.height || j >= data->map.width)
		return false;
	// if (map[i][j] == '1')
	// 	return (true);
	// return (false);
	j = x / TILE_SIZE;
	i = (y + P_RAD) / TILE_SIZE;
	j = x / TILE_SIZE;
	if (map[i][j] == '1')
		return (true);
	i = (y - P_RAD) / TILE_SIZE;
	if (map[i][j] == '1')
		return (true);
	i = y / TILE_SIZE;
	j = (x + P_RAD) / TILE_SIZE;
	if (map[i][j] == '1')
		return (true);
	j = (x - P_RAD) / TILE_SIZE;
	if (map[i][j] == '1')
		return (true);
	return (false);
}

// int	update_player(t_data *data, t_player player_ins)
int	update_player(t_data *data)
{
	t_player	*player;
	double		new_x,new_y;
	double		walk_inside;

	player = &data->player;
	player->img =  reset_img(data);
	player->angle += player->rotation_angle * ROT_SPEED;
	walk_inside = 0;
	if (abs(player->walk_direction) == 2)
	{
		player->walk_direction /= 2;
		walk_inside = degtorad(90);
	}
	int move_step = player->walk_direction * MOVE_SPEED;
	new_x = player->x + (cos(player->angle + walk_inside) * move_step);
	new_y = player->y + (sin(player->angle + walk_inside) * move_step);
	if (!is_wall(data, new_x, new_y))
		(1) && (player->x = new_x, player->y = new_y);
	draw_player(data);
	cast_rays(data->map, data->player ,&data->rays);
	project_walls(data);
	player->walk_direction = 0;
	player->rotation_angle = 0;
	return (1);
}


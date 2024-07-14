/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:51:11 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/14 09:01:02 by emagueri         ###   ########.fr       */
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

t_player new_player(t_data *data, int x, int y)
{
	t_player player;

	player.img = mlx_new_image(data->mlx, TILE_SIZE * 20, TILE_SIZE * 20);
	player.x = x;
	player.y = y;
	player.angle = degtorad(DEG);
	player.rotation_angle = 0;
	player.rotation_speed = 3;
	player.walk_direction = 0;
	player.move_speed = 3;
	player.radius = 150;
	data->player = player;
	return player;
}
// void new_player(t_data *data, t_point p, mlx_image_t *img)
// {
// 	t_player player;

// 	player = data->player;
// 	data->player.x = p.x;
// 	data->player.y = p.y;
// 	data->player.angle = degtorad(-50);
// 	data->player.rotation_angle = 0;
// 	data->player.rotation_speed = 3;
// 	data->player.walk_direction = 0;
// 	data->player.move_speed = 3;
// 	data->player.radius = TILE_SIZE/4;
// 	data->player.img = img;
// 	create_vector_player(data, p);
// }

int create_vector_player(t_data *data)
{
	t_player player = data->player;
	t_point p2;

	p2 = new_point(
		data->player.x + (cos(player.angle) * player.radius),
		data->player.y + (sin(player.angle) * player.radius)
	);
	draw_line(data, new_point(data->player.x, data->player.y),
				p2, 0xFFFF00FF, data->player.img);
	return (1);
}

int draw_player(t_data *data, t_point point_image)
{
	mlx_image_t	*img;
	int			radius;
	t_player player;

	player = data->player;
	radius = 8;
	img = data->player.img;
	t_circle c = new_circle(point_image.x, point_image.y, 8, 0xFF0000FF);
	draw_circle(c, img);
	create_vector_player(data);
	// mlx_image_to_window(data->mlx, img, 0, 0);
	data->player_img = img;
	return (1);
}

void	ft_reset_img(mlx_image_t *img)
{
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++)
			mlx_put_pixel(img,j,i, 0);	
}

// int	update_player(t_data *data, t_player player_ins)
int	update_player(t_data *data)
{
	double			x,y;
	double			new_x,new_y;
	t_player	*player;

	player = &data->player;
	x = player->x;
	y = player->y;
	ft_reset_img(player->img);
	double angle_rotate = player->rotation_angle * player->rotation_speed;
	player->angle += angle_rotate;
	double walk_inside = 0;
	if (abs(player->walk_direction) == 2)
	{
		player->walk_direction /= 2;
		walk_inside = degtorad(90);
	}
	int move_step = player->walk_direction * 3;
	new_x = player->x + (cos(player->angle + walk_inside) * move_step);
	new_y = player->y + (sin(player->angle + walk_inside) * move_step);
	player->x = new_x;
	player->y = new_y;
	draw_player(data, new_point(new_x, new_y));
	player->walk_direction = 0;
	player->rotation_angle = 0;
	return (1);
}


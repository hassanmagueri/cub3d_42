/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:51:11 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/13 17:10:07 by emagueri         ###   ########.fr       */
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

t_player new_player(t_data *data)
{
	t_player player;

	player.img = mlx_new_image(data->mlx, TILE_SIZE * 20, TILE_SIZE * 20);
	player.x = player.img->width / 2;
	player.y = player.img->height / 2;
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
		data->player.img->width / 2 + (cos(player.angle) * player.radius),
		data->player.img->height / 2 + (sin(player.angle) * player.radius)
	);
	draw_line(data, new_point(data->player.img->width / 2, data->player.img->height / 2),
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
	t_circle c = new_circle(player.x, player.y, 8, 0xFF0000FF);
	draw_circle(c, img);
	create_vector_player(data);
	mlx_image_to_window(data->mlx, img, 0, 0);
	data->player_img = img;
	return (1);
}

// int	update_player(t_data *data, t_player player_ins)
int	update_player(t_data *data)
{
	int			x,y;
	static double old_x;
	static double old_y;
	int			new_x,new_y;
	// t_player	player;

	x = data->player.img->instances[0].x;
	y = data->player.img->instances[0].y;
	
	data->player.img = clear_image(data->mlx, data->player.img);
	double angle_rotate = data->player.rotation_angle * data->player.rotation_speed;
	printf("angle rotation %f\n", radtodeg(angle_rotate));
	// data->player = player;

	
	int move_step = data->player.walk_direction * 3;
	printf("move step : %d\n", move_step);
	printf("angle %f\n", data->player.angle);
	data->player.angle += angle_rotate;
	new_x = lround(x + (cos(data->player.angle) * move_step));
	new_y = lround(y + (sin(data->player.angle) * move_step));
	printf("old x : %d\n", x);
	printf("old y : %d\n", y);
	printf("new x : %d\n", new_x);
	printf("new cos : %f\n", cos(data->player.angle));
	printf("new y : %d\n", new_y);
	printf("new sin : %f\n", sin(data->player.angle));
	draw_player(data, new_point(new_x, new_y));

	// old_x = x + (cos(data->player.angle) * move_step);
	// old_y = x + (sin(data->player.angle) * move_step);
	// data->player.x = 
	
	printf("------------------------------\n");
	data->player.walk_direction = 0;
	data->player.rotation_angle = 0;
	return (1);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:04:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/01 22:33:42 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#include "MLX42.h"

double ray_distance(double dx, double dy)
{
	return (sqrt(pow(dx, 2) + pow(dy, 2)));
}

void project_walls(t_data *data)
{
	int i;
	t_ray *rays;
	double  ray_dist;
	// double dist_prj_plane = (WIDTH / 2) / tan(FOV / 2);
	double wall_expected_height;
	static mlx_image_t *img;
	
	rays = data->rays;
	i = 0;
	if (img)
		mlx_delete_image(data->mlx, img);
	img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	for(int i = 0; i < img->height; i++)
		for(int j = 0; j < img->width; j++)
			mlx_put_pixel( img, j, i, 0X10A27755);
	mlx_image_to_window(data->mlx, img, data->map.width * TILE_SIZE,0);
	while (i < NUM_RAYS)
	{
		double correct_ray;
		
		ray_dist = ray_distance(rays[i].dx, rays[i].dy);
		correct_ray = ray_dist * cos(rays[i].angle - data->player.angle);
		wall_expected_height = (TILE_SIZE  * 600 / correct_ray) ;
		int color = (rays[i].is_vr && rays[i].direct == 1) ? WHITE : BLUE;
		if (rays[i].is_vr && rays[i].direct == 1)
			color = WHITE;
		else if (rays[i].is_vr && rays[i].direct == -1)
			color = YELLOW;
		else if (!rays[i].is_vr && rays[i].direct == 1)
			color = BLUE;
		else if (!rays[i].is_vr && rays[i].direct == -1)
			color = GREY;
		// color = (rays[i].is_vr && rays[i].direct == -1) ? YELLOW : GREY;
		draw_wall(
			(t_wall){i, (HEIGHT / 2) - (wall_expected_height / 2), 1, wall_expected_height, color},
			img
		);
		i++;
	}
}
 
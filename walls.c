/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:04:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/25 18:35:27 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

double ray_distance(double dx, double dy)
{
	return (sqrt(pow(dx, 2) + pow(dy, 2)));
}

void project_walls(t_data *data)
{
	int i;
	t_ray *rays;
	double  ray_dist;
	double dist_prj_plane = (WIDTH / 2) / tan(FOV / 2);
	double wall_expected_height;
	static mlx_image_t *img;
	
	rays = data->rays;
	i = 0;

	if (img)
		mlx_delete_image(data->mlx, img);
	img = new_image_to_window(data->mlx, WIDTH, HEIGHT);
	// mlx_image_t *img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	// mlx_image_to_window(data->mlx, img, 0, 0);
	// mlx_delete_image(data->mlx, img);
	while (i < NUM_RAYS)
	{
		printf("%d\n", i);
		ray_dist = ray_distance(rays[i].dx, rays[i].dy);
		wall_expected_height = (TILE_SIZE / ray_dist) * dist_prj_plane;
		draw_wall(
			(t_wall){i, (HEIGHT / 2) - (wall_expected_height / 2), 1, wall_expected_height, WHITE},
			img
		);
		i++;
	}
	mlx_image_to_window(data->mlx, img, 0, 0);
	// mlx_image_to_window(data->mlx, img);
}
 
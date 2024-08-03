/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:04:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/03 21:56:55 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#include "MLX42.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

double ray_distance(double dx, double dy)
{
	return (sqrt(pow(dx, 2) + pow(dy, 2)));
}

char *swap_bytes(char *str)
{
	unsigned char tmp;

	tmp = str[0];
	str[0] = str[3];
	str[3] = tmp;
	tmp = str[2];
	str[2] = str[1];
	str[1] = tmp;
	return str;
}

void	ft_put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	swap_bytes((char *)(&color));
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
				mlx_put_pixel(img, x, y, color);
}


// int	wall_painting(t_data *data, t_ray ray , double ray_dist , double wall_height, mlx_image_t *img , int x)
// {
// 	t_map map=data->map;
// 	uint32_t *p_clrs = (uint32_t *)data->texture->pixels;
// 	int i;
	
// 	i = 0;
// 	double wall_top_pixel=((HEIGHT) / 2) - (wall_height / 2);
// 	if (wall_top_pixel < 0)
// 		wall_top_pixel = 0;
// 	int x_col = ray.is_vr ? 0: (int)(data->player.x + ray.dx * ray.direct) % data->texture->width;

// 	// p_clrs[x_col + img->width];
// 	double wall_bottom_pixel=((HEIGHT) /2) + (wall_height/ 2);
	
// 	if(wall_bottom_pixel > (HEIGHT))
// 		wall_bottom_pixel = HEIGHT ;
// 	int y = 0;
// 	while (wall_top_pixel <= wall_bottom_pixel && (y < data->texture->height))
// 	{
// 		int size_bytes = (wall_height / data->texture->height);
		
// 		i = 0;
			
// 		while (i < size_bytes)
// 		{
// 			ft_put_pixel(img, x, wall_top_pixel , p_clrs[x_col + (data->texture->width * y)]);
// 			i++;
// 		}
// 		if (i == 0)
// 		{
// 			ft_put_pixel(img, x, wall_top_pixel , p_clrs[x_col + (data->texture->width * y - )]);
// 			size_bytes++;
// 		}
// 		y++;
// 		wall_top_pixel += size_bytes;
// 	}
	
// 	return (1);
// }

int wall_painting(t_data *data, t_ray ray, double ray_dist, double wall_height, mlx_image_t *img, int ray_index) {
	t_map map = data->map;
	uint32_t *p_clrs = (uint32_t *)data->texture->pixels;
	static int n;
	n++;
	double wall_top_pixel = (HEIGHT / 2) - (wall_height / 2);
	if (wall_top_pixel < 0) wall_top_pixel = 0;

	double wall_hit_x = data->player.x + ray.dx * ray.direct;
	double wall_hit_y = data->player.y + ray.dy * ray.direct;
	// double wall_hit;

	int x_col;
	if (ray.is_vr)
	{
		x_col = (int)wall_hit_y % data->texture->width;
		// wall_hit
	}
	else
		x_col = (int)wall_hit_x % data->texture->width;

	double wall_bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
	if (wall_bottom_pixel > HEIGHT) wall_bottom_pixel = HEIGHT;

	int y = wall_top_pixel;
	unsigned long index = 0;
	while (wall_top_pixel <= wall_bottom_pixel && index < data->texture->width * data->texture->height)
	{
		int dist_top_text = y + (wall_height / 2) - (HEIGHT / 2);
		int offY = dist_top_text * data->texture->height / wall_height;
		index = (data->texture->width * offY) + x_col;
		if (index < data->texture->height * data->texture->width)
			ft_put_pixel(img, ray_index , (int)wall_top_pixel, p_clrs[index]);
		wall_top_pixel++;
		y++;
	}
	printf("y: %d\n", y);

	return 1;
}

void project_walls(t_data *data)
{
	
	int i;
	t_ray *rays;
	double  ray_dist;
	double wall_expected_height;
	static mlx_image_t *img;
	
	rays = data->rays;
	i = 0;
	if (img)
		mlx_delete_image(data->mlx, img);
	img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, img, 0,0);
	while (i < NUM_RAYS)
	{
		double correct_ray;
		
		ray_dist = ray_distance(rays[i].dx, rays[i].dy);
		correct_ray = ray_dist * cos(rays[i].angle - data->player.angle);
		wall_expected_height = (data->texture->height * 600 / correct_ray) ;
		wall_painting(data,rays[i], ray_dist, wall_expected_height, img ,  i);
		i++;
	}
}
 
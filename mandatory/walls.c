/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:04:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/13 11:01:03 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

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

void ft_put_pixel(mlx_image_t *img, size_t x, size_t y, uint32_t color)
{
	swap_bytes((char *)(&color));
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

int painting_part_col(mlx_image_t *img, int start, int end, int x, t_clr color)
{
	int y = start;
	while (y < end)
	{
		mlx_put_pixel(img, x, y, ft_pixel(color));
		y++;
	}
	return 0;
}

int wall_painting(t_data *data, t_ray ray,
				  mlx_image_t *img, int x, mlx_texture_t *texture){
	uint32_t *p_clrs = (uint32_t *)texture->pixels;
	(void)img;
	double wall_top_pixel = (WINDOW_HEIGHT / 2) - (data->wall_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	double wall_hit_x = data->player.x + ray.dx;
	double wall_hit_y = data->player.y + ray.dy;

	int offX;
	if (ray.is_vr)
		offX = (int)wall_hit_y % texture->width;
	else
		offX = (int)wall_hit_x % texture->width; 

	double wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (data->wall_height / 2);
	if (wall_bottom_pixel > WINDOW_HEIGHT)
		wall_bottom_pixel = WINDOW_HEIGHT;

	int y = 0;
	unsigned long index = 0;
	y = wall_top_pixel;
	while (y <= wall_bottom_pixel && index < texture->width * texture->height)
	{
		int dist_top_text = y - WINDOW_HEIGHT / 2 + data->wall_height / 2;
		int offY = dist_top_text * texture->height / data->wall_height;
		index = (texture->width * offY) + offX;
		if (index < texture->height * texture->width)
			ft_put_pixel(img, x, y, p_clrs[index]);
		y++;
	}
	return (1);
}

void project_walls(t_data *data, t_ray ray, int x)
{

	double ray_dist;
	t_textures textures;
	static mlx_image_t *img;

	img = data->window_img;
	int distanceProjectionPlane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	textures = data->textures;
	double correct_ray;

	ray_dist = ray_distance(ray.dx, ray.dy);
	correct_ray = ray_dist * cos(ray.angle - data->player.angle);
	data->wall_height = (TILE_SIZE / correct_ray * distanceProjectionPlane);
	if (ray.direct == -1 && ray.is_vr)
		wall_painting(data, ray ,img, x, textures.NO);
	else if (ray.direct == -1 && !ray.is_vr)
		wall_painting(data, ray, img, x, textures.SO);
	else if (ray.direct == 1 && ray.is_vr)
		wall_painting(data, ray, img, x, textures.WE);
	else if (ray.direct == 1 && !ray.is_vr)
		wall_painting(data, ray, img, x, textures.EA);
}

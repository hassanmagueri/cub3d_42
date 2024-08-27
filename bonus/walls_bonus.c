/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:04:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/27 02:28:55 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	ray_distance(double dx, double dy)
{
	return (sqrt(pow(dx, 2) + pow(dy, 2)));
}

char	*swap_bytes(char *str)
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

void	ft_put_pixel( t_data *data, int y, uint32_t color)
{
	swap_bytes((char *)(&color));
	if (data->x_ray>= 0 && (size_t)data->x_ray < data->window_img->width 
		&& y >= 0 && (size_t)y < data->window_img->height)
		mlx_put_pixel(data->window_img, data->x_ray, y, color);
}

int		painting_part_col(mlx_image_t *img, int start, int end, int x)
{
	int y = start;
	while (y < end)
		mlx_put_pixel(img, x, y++, 0);
	return 0;
}
int	get_distance_door(t_data *data, double x, double y)
{
	int p_x = data->player.x / TILE_SIZE;
	int p_y = data->player.y / TILE_SIZE;
	int d_x = (int)x;
	int d_y = (int)y;
	return abs(d_x - p_x) + abs(d_y - p_y);
}

double	wall_top_pixle(double wall_height)
{
	double wall_top_pixel;

	wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	return (wall_top_pixel);
}
int	ret_offset_x(double wall_hit_x, double wall_hit_y,
				 bool is_vr, mlx_texture_t *texture)
{
	int offset_x;

	if (is_vr)
		offset_x = (int)wall_hit_y % texture->width;
	else
		offset_x = (int)wall_hit_x % texture->width;
	return (offset_x);
}
void render_texture(t_data *data, double wall_height,
					double wall_bottom_pixel, mlx_texture_t *texture)
{
	double wall_top_pixel;
	unsigned long index;
	int dist_top_text;
	int offsety;
	int y;

	wall_top_pixel = wall_top_pixle(wall_height);
	painting_part_col(data->window_img, 0, wall_top_pixel, data->x_ray);
	y = wall_top_pixel;
	index = 0;
	while (y <= wall_bottom_pixel && index < texture->width * texture->height)
	{
		dist_top_text = y - WINDOW_HEIGHT / 2 + wall_height / 2;
		offsety = dist_top_text * texture->height / wall_height;
		index = (texture->width * offsety) + data->offsetx;
		if (index < texture->height * texture->width)
			ft_put_pixel(data, y, data->p_clrs[index]);
		y++;
	}
	painting_part_col(data->window_img, wall_bottom_pixel, WINDOW_HEIGHT, data->x_ray);
}
int wall_painting(t_data *data, t_ray ray,
				  double wall_height, int x, mlx_texture_t *texture)
{
	uint32_t *p_clrs;
	int offsetx;
	double wall_hit_x;
	double wall_hit_y;
	double wall_bottom_pixel;

	p_clrs = (uint32_t *)texture->pixels;
	wall_hit_x = data->player.x + ray.dx;
	wall_hit_y = data->player.y + ray.dy;
	if (draw_doors(data, wall_hit_x, wall_hit_y, ray))
	{
		texture = data->tex_door;
		p_clrs = (uint32_t *)data->tex_door->pixels;
	}
	offsetx = ret_offset_x(wall_hit_x, wall_hit_y, ray.is_vr, texture);
	wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_height / 2);
	if (wall_bottom_pixel > WINDOW_HEIGHT)
		wall_bottom_pixel = WINDOW_HEIGHT;
	data->offsetx = offsetx;
	data->x_ray = x;
	data->p_clrs = p_clrs;
	render_texture(data, wall_height, wall_bottom_pixel, texture);
	return (1);
}

void	project_walls(t_data *data, t_ray ray, int x)
{
	t_textures textures;
	int distance_projection_plane;
	double ray_dist;
	double correct_ray;
	double wall_expected_height;

	distance_projection_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	textures = data->textures;
	ray_dist = ray_distance(ray.dx, ray.dy);
	correct_ray = ray_dist * cos(ray.angle - data->player.angle);
	wall_expected_height = (TILE_SIZE * (TILE_SIZE + TILE_SIZE / 2) / correct_ray );
	if (ray.direct == -1 && ray.is_vr)
		wall_painting(data, ray, wall_expected_height, x, textures.NO);
	else if (ray.direct == -1 && !ray.is_vr)
		wall_painting(data, ray, wall_expected_height, x, textures.SO);
	else if (ray.direct == 1 && ray.is_vr)
		wall_painting(data, ray, wall_expected_height, x, textures.WE);
	else if (ray.direct == 1 && !ray.is_vr)
		wall_painting(data, ray, wall_expected_height, x, textures.EA);
}

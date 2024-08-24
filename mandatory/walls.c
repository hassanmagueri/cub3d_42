/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:04:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/24 15:09:16 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	ft_put_pixel(mlx_image_t *img, size_t x
		, size_t y, uint32_t color)
{
	swap_bytes((char *)(&color));
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
		mlx_put_pixel(img, x, y, color);
}

double	wall_top_pixle(double wall_height)
{
	double	wall_top_pixel;

	wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	return (wall_top_pixel);
}

void	render_texture(t_data *data, double wall_height,
			double wall_bottom_pixel, mlx_texture_t *texture)
{
	unsigned long	index;
	uint32_t		*p_clrs;
	int				y_ver;
	int				offsety;
	int				dist_top_text;

	index = 0;
	p_clrs = (uint32_t *)texture->pixels;
	y_ver = wall_top_pixle(wall_height);
	while (y_ver <= wall_bottom_pixel
		&& index < texture->width * texture->height)
	{
		dist_top_text = y_ver - (WINDOW_HEIGHT / 2) + (wall_height / 2);
		offsety = dist_top_text * texture->height / wall_height;
		index = (texture->width * offsety) + data->offsetx;
		if (index < texture->height * texture->width)
			ft_put_pixel(data->window_img, data->x_ray, y_ver, p_clrs[index]);
		y_ver++;
	}
}

int	wall_painting(t_data *data, t_ray ray, int x, mlx_texture_t *texture)
{
	uint32_t	*p_clrs;
	double		wall_bottom_pixel;
	int			offsetx;
	double		wall_hit_x;
	double		wall_hit_y;

	p_clrs = (uint32_t *)texture->pixels;
	wall_hit_x = data->player.x + ray.dx;
	wall_hit_y = data->player.y + ray.dy;
	offsetx = ret_offset_x(wall_hit_x, wall_hit_y, ray.is_vr, texture);
	wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (data->wall_height / 2);
	if (wall_bottom_pixel > WINDOW_HEIGHT)
		wall_bottom_pixel = WINDOW_HEIGHT;
	data->offsetx = offsetx;
	data->x_ray = x;
	render_texture(data, data->wall_height, wall_bottom_pixel, texture);
	return (1);
}

void	project_walls(t_data *data, t_ray ray, int x)
{
	t_textures	textures;
	double		ray_dist;
	double		correct_ray;
	int			distance_projection_plane;

	distance_projection_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	textures = data->textures;
	ray_dist = ray_distance(ray.dx, ray.dy);
	correct_ray = ray_dist * cos(ray.angle - data->player.angle);
	data->wall_height = (TILE_SIZE / correct_ray * distance_projection_plane);
	if (ray.direct == -1 && ray.is_vr)
		wall_painting(data, ray, x, textures.NO);
	else if (ray.direct == -1 && !ray.is_vr)
		wall_painting(data, ray, x, textures.SO);
	else if (ray.direct == 1 && ray.is_vr)
		wall_painting(data, ray, x, textures.WE);
	else if (ray.direct == 1 && !ray.is_vr)
		wall_painting(data, ray, x, textures.EA);
}

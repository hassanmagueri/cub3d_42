/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:04:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/27 15:27:57 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	wall_top_pixle(double wall_height)
{
	double	wall_top_pixel;

	wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	return (wall_top_pixel);
}

int	ret_offset_x(double wall_hit_x, double wall_hit_y,
			bool is_vr, mlx_texture_t *texture)
{
	int	offset_x;

	if (is_vr)
		offset_x = (int)wall_hit_y % texture->width;
	else
		offset_x = (int)wall_hit_x % texture->width;
	return (offset_x);
}

void	render_texture(t_data *data, double wall_height,
		double wall_bottom_pixel, mlx_texture_t *texture)
{
	double			wall_top_pixel;
	unsigned long	index;
	int				dist_top_text;
	int				offsety;
	int				y;

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
	painting_part_col(data->window_img,
		wall_bottom_pixel, WINDOW_HEIGHT, data->x_ray);
}

int	wall_painting(t_data *data, t_ray ray, int x, mlx_texture_t *texture)
{
	uint32_t	*p_clrs;
	int			offsetx;
	double		wall_hit_x;
	double		wall_hit_y;
	double		wall_bottom_pixel;

	p_clrs = (uint32_t *)texture->pixels;
	wall_hit_x = data->player.x + ray.dx;
	wall_hit_y = data->player.y + ray.dy;
	if (draw_doors(data, wall_hit_x, wall_hit_y, ray))
	{
		texture = data->tex_door;
		p_clrs = (uint32_t *)data->tex_door->pixels;
	}
	offsetx = ret_offset_x(wall_hit_x, wall_hit_y, ray.is_vr, texture);
	wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (data->wall_height / 2);
	if (wall_bottom_pixel > WINDOW_HEIGHT)
		wall_bottom_pixel = WINDOW_HEIGHT;
	data->offsetx = offsetx;
	data->x_ray = x;
	data->p_clrs = p_clrs;
	render_texture(data, data->wall_height, wall_bottom_pixel, texture);
	return (1);
}

void	project_walls(t_data *data, t_ray ray, int x)
{
	t_textures	textures;
	int			distance_projection_plane;
	double		ray_dist;
	double		correct_ray;

	distance_projection_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	textures = data->textures;
	ray_dist = ray_distance(ray.dx, ray.dy);
	correct_ray = ray_dist * cos(ray.angle - data->player.angle);
	data->wall_height \
		= (TILE_SIZE * (TILE_SIZE + TILE_SIZE / 2) / correct_ray);
	if (ray.direct == -1 && !ray.is_vr)
		wall_painting(data, ray, x, textures.NO);
	else if (ray.direct == -1 && ray.is_vr)
		wall_painting(data, ray, x, textures.WE);
	else if (ray.direct == 1 && ray.is_vr)
		wall_painting(data, ray, x, textures.EA);
	else if (ray.direct == 1 && !ray.is_vr)
		wall_painting(data, ray, x, textures.SO);
}

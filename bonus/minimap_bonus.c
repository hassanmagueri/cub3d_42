/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:56:00 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/25 03:06:15 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

int	draw_react_minimap(t_rect rect, mlx_image_t *image, int width, int height)
{
	double	i;
	double	j;

	i = rect.y;
	while (i <= rect.y + height)
	{
		j = rect.x;
		while (j <= rect.x + width)
		{
			if (j >= 0 && i >= 0 && j <= image->width && i <= image->height)
				mlx_put_pixel(image, j, i, rect.color);
			j++;
		}
		i++;
	}
	return (1);
}

int	border_minimap(mlx_image_t *img, t_circle c)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < img->width)
		{
			if (pow(j - c.x, 2) + pow(i - c.y, 2) >= pow(img->width / 2 - 16, 2)
				&& pow(j - c.x, 2) + pow(i - c.y, 2)
				< pow(img->width / 2 - 8, 2)
			)
				mlx_put_pixel(img, j, i, BLACK);
			if (pow(j - c.x, 2) + pow(i - c.y, 2) >= pow(img->width / 2 - 8, 2))
				mlx_put_pixel(img, j, i, 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	index_scale(double p1, double p2, int index_p, int index)
{
	int	player_off_tile;

	player_off_tile = p1
		- ((int)(p2 / TILE_SIZE)*TILE_SIZE + TILE_SIZE / 2) * SCALE;
	return ((int)
		((index + index_p * SCALE_SIZE + player_off_tile) / SCALE_SIZE));
}

bool	is_out(int i_scale, int j_scale, t_minimap minimap, t_map map)
{
	return (i_scale - (int)minimap.pn.y < 0 || j_scale - (int)minimap.pn.x < 0
		|| i_scale >= map.height || j_scale >= map.width);
}

int	wall_col_putpixel(t_minimap minimap, t_player player,
	t_map map, t_index ind)
{
	int	i_scl;
	int	j_scl;

	i_scl = index_scale(minimap.player_p.y, player.y, minimap.start_p.y, ind.i)
		- minimap.pn.y;
	j_scl = index_scale(minimap.player_p.x, player.x, minimap.start_p.x, ind.j)
		- minimap.pn.x;
	if (is_out(i_scl, j_scl, minimap, map) || i_scl == 0)
		mlx_put_pixel(minimap.img, ind.j, ind.i, GREY);
	else if (map.layout[i_scl][j_scl] == 'C')
		mlx_put_pixel(minimap.img, ind.j, ind.i, SEMI_YELLOW);
	else if (map.layout[i_scl][j_scl] == '1')
		mlx_put_pixel(minimap.img, ind.j, ind.i, GREY);
	return (1);
}

int	walls(t_data data)
{
	int			i;
	int			j;
	t_player	player;
	t_minimap	minimap;

	player = data.player;
	minimap = data.minimap;
	i = 0;
	while (i < MINIMAP_HEIGHT * SCALE_SIZE)
	{
		j = 0;
		while (j < MINIMAP_WIDTH * SCALE_SIZE)
		{
			wall_col_putpixel(minimap, player, data.map, (t_index){i, j});
			j++;
		}
		i++;
	}
	return (1);
}

int	set_walls(t_data *data)
{
	data->minimap.player_p.x = data->player.x * SCALE;
	data->minimap.player_p.y = data->player.y * SCALE;
	data->minimap.start_p.x = data->player.x / TILE_SIZE - MINIMAP_WIDTH / 2;
	data->minimap.start_p.y = data->player.y / TILE_SIZE - MINIMAP_HEIGHT / 2;
	data->minimap.pn.x = 0;
	data->minimap.pn.y = 0;
	if (data->minimap.player_p.x <= 5 * SCALE_SIZE)
		data->minimap.pn.x = 1;
	if (data->minimap.player_p.y <= 5 * SCALE_SIZE)
		data->minimap.pn.y = 1;
	walls(*data);
	return (1);
}

int	set_rays(t_player player, mlx_image_t *img, t_map map, t_ray rays[NUM_RAYS])
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = (img->width - img->width / 2);
	y = (img->height - img->height / 2);
	while (i < NUM_RAYS)
	{
		draw_line(
			new_line(
				(t_point){x, y},
				(t_point){rays[i].dx * SCALE + x, (rays[i].dy * SCALE + y)},
				YELLOW),
			img
			);
		i++;
	}
	return (1);
}

int	reset_minimap(mlx_image_t *img, t_circle c)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			if (pow(j - c.x, 2) + pow(i - c.y, 2) < pow(img->width / 2, 2))
				mlx_put_pixel(img, j, i, SEMI_WHITE);
			j++;
		}
		i++;
	}
	return (0);
}

int	draw_minimap(t_data *data)
{
	mlx_image_t	*img;
	t_player	player;
	t_circle	c;
	t_line		line;

	player = data->player;
	img = data->minimap.img;
	c = new_circle(img->width / 2, img->height / 2, player.radius, SEMI_LIME);
	reset_minimap(img, c);
	draw_circle(c, img);
	set_walls(data);
	line = new_line(
			new_point(img->width / 2, img->height / 2),
			new_point(
				(img->width / 2 + (cos(player.angle) * 50 * SCALE_SIZE)
					* SCALE),
				(img->height / 2 + (sin(player.angle) * 50 * SCALE_SIZE)
					* SCALE)
				), WHITE
			);
	draw_line(line, img);
	border_minimap(img, c);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:36:09 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/27 04:17:20 by emagueri         ###   ########.fr       */
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

int	reset_minimap(mlx_image_t *img, t_circle c)
{
	int	i;
	int	j;

	i = 0;
	while ((size_t)i < img->height)
	{
		j = 0;
		while ((size_t)j < img->width)
		{
			if (pow(j - c.x, 2) + pow(i - c.y, 2) < pow(img->width / 2, 2))
				mlx_put_pixel(img, j, i, SEMI_DARK);
			j++;
		}
		i++;
	}
	return (0);
}

bool	is_out(int i_scale, int j_scale, t_map map)
{
	return ((double)i_scale < 0 || (double)j_scale < 0
		|| (size_t)i_scale >= map.height || (size_t)j_scale >= map.width);
}

int	set_rays(mlx_image_t *img, t_ray rays[NUM_RAYS])
{
	long	color;
	int		i;
	int		x;
	int		y;

	color = YELLOW;
	i = 0;
	x = (img->width - img->width / 2);
	y = (img->height - img->height / 2);
	while (i < NUM_RAYS)
	{
		draw_line(
			new_line(
				(t_point){x, y},
				(t_point){rays[i].dx * SCALE + x, (rays[i].dy * SCALE + y)},
				color),
			img
			);
		i++;
	}
	return (1);
}

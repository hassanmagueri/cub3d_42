/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_help_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:30:52 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/25 03:17:22 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

mlx_image_t	*reset_img(mlx_image_t *img)
{
	size_t i;
	for (i = 0; i  < img->width; i++)
	{
		size_t j;
		for (j = 0; j < img->height; j++)
			mlx_put_pixel(img, i, j, 0);
	}
	return img;
}

t_line new_line(t_point p1,t_point p2, int color)
{
	t_line line;

	line.p1.x = p1.x;
	line.p1.y = p1.y;
	line.p2.x = p2.x;
	line.p2.y = p2.y;
	line.color = color;
	return (line);
}

int32_t ft_pixel(t_clr color)
{
	uint8_t r = color.red;
	uint8_t g = color.green;
	uint8_t b = color.blue;
	
	return (r << 24 | g << 16 | b << 8 | 255);
}
t_rect new_rect(int x, int y, int side, int color)
{
	t_rect	rect;

	rect.x = x;
	rect.y = y;
	rect.side = side;
	rect.color = color;
	return rect;
}

t_circle new_circle(int x, int y, int radius, int color)
{
	t_circle	circle;

	circle.x = x;
	circle.y = y;
	circle.radius = radius;
	circle.color = color;
	return circle;
}
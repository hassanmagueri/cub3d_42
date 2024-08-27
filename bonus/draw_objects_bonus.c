/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objects_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:46 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/27 04:20:09 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

int	border_minimap(mlx_image_t *img, t_circle c)
{
	int	i;
	int	j;

	i = 0;
	while ((size_t)i < img->width)
	{
		j = 0;
		while ((size_t)j < img->width)
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

void	put_pixels_line(mlx_image_t *image, t_line line, double steps)
{
	int		i;
	float	x;
	float	y;
	float	xinc;
	float	yinc;

	xinc = (line.p2.x - line.p1.x) / steps;
	yinc = (line.p2.y - line.p1.y) / steps;
	x = line.p1.x;
	y = line.p1.y;
	i = 0;
	while (i <= steps && x < image->width && y < image->height
		&& (line.color * 2) % 255)
	{
		if (x < image->width && x >= 0 && y >= 0 && y < image->height)
			mlx_put_pixel(image, x, y, line.color -= 2);
		x += xinc;
		y += yinc;
		i++;
	}
}

int	draw_line(t_line line, mlx_image_t *image)
{
	float	dx;
	float	dy;
	double	steps;

	dx = fabs(line.p1.x - line.p2.x);
	dy = fabs(line.p1.y - line.p2.y);
	if (dx == 0)
		dx = 1;
	if (dy == 0)
		dy = 1;
	steps = fabs(dy);
	if (dx > dy)
		steps = fabs(dx);
	put_pixels_line(image, line, steps);
	return (1);
}

int	draw_circle(t_circle circle, mlx_image_t *image)
{
	int	x;
	int	y;

	x = (circle.x - circle.radius);
	while (x < (circle.x + circle.radius))
	{
		y = (circle.y - circle.radius);
		while (y < (circle.y + circle.radius))
		{
			if ((pow(x - circle.x, 2) + pow(y - circle.y, 2))
				< pow(circle.radius, 2)
				&& (size_t)x < image->width && (size_t)y < image->height)
				mlx_put_pixel(image, x, y, circle.color);
			y++;
		}
		x++;
	}
	return (1);
}

int	draw_react(t_rect rect, mlx_image_t *image)
{
	double	i;
	double	j;

	i = rect.x;
	while (i <= rect.x + rect.side)
	{
		j = rect.y;
		while (j <= rect.y + rect.side)
		{
			mlx_put_pixel(image, j, i, rect.color);
			j++;
		}
		i++;
	}
	return (1);
}

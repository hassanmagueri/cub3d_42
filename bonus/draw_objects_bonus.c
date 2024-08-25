/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objects_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:46 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/25 15:44:49 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"
#include <math.h>

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
	while (i <= steps && x < image->width && y < image->height)
	{
		if (x < image->width && x >= 0 && y >= 0 && y < image->height)
			mlx_put_pixel(image, x, y, line.color);
		x += xinc;
		y += yinc;
		line.color--;
		line.color--;
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

t_point	new_point(double x, double y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

int	draw_circle(t_circle circle, mlx_image_t *image)
{
	int	x;
	int	y;

	x = circle.x - circle.radius;
	while (x < circle.x + circle.radius)
	{
		y = circle.y - circle.radius;
		while (y < circle.y + circle.radius)
		{
			if ((pow(x - circle.x, 2) + pow(y - circle.y, 2))
				< pow(circle.radius, 2)
				&& x < image->width && y < image->height)
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

int	draw_wall(t_wall wall, mlx_image_t *image)
{
	double	i;
	double	j;

	i = wall.x;
	while (i < (wall.x + wall.width))
	{
		j = wall.y;
		while (j < (wall.y + wall.height))
		{
			if (i <= image->width && i >= 0 && j >= 0 && j <= image->height)
				mlx_put_pixel(image, i, j, wall.color);
			j++;
		}
		i++;
	}
	return (1);
}

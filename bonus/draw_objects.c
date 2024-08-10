/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:46 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/09 11:15:33 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int draw_line(t_line line, mlx_image_t *image)
{
	t_point p1 = line.p1;
	t_point p2 = line.p2;
	int i;
	float dx = fabs(p1.x - p2.x) == 0 ? 1 : fabs(p1.x - p2.x);
	float dy = fabs(p1.y - p2.y) == 0 ? 1: fabs(p1.y - p2.y);
	double steps = dx > dy ? fabs(dx) : fabs(dy);
	float xinc = (p2.x - p1.x) / steps;
	float yinc =  (p2.y - p1.y) / steps;

	i = 0;
	float X = p1.x;
	float Y = p1.y;


	if (xinc == 0 && yinc == 0)
		return 1;
	for (int i = 0; i <= steps && X < image->width && Y < image->height; i++)
	{
		if (X < image->width && X >= 0 && Y >= 0 && Y < image->height)
			mlx_put_pixel(image, X, Y, line.color);
		X += xinc;
		Y += yinc;
		line.color--;
		line.color--;
	}
	return (1);
}

t_point	new_point(double x, double y)
{
	t_point p;

	p.x = x;
	p.y = y;
	return p;
}

void set_background(mlx_image_t *image, int color)
{
	for (size_t i = 0; i < image->height; i++)
	{
		for (size_t j = 0; j < image->width; j++)
			mlx_put_pixel(image, j, i, color);
	}
}

int	draw_circle(t_circle circle, mlx_image_t *image)
{
	int x;
	int y;

	// set_background(image, BACKGROUND);
	// x = center.x - radius;
	x = circle.x - circle.radius;
	while (x < circle.x + circle.radius)
	{
		y = circle.y - circle.radius;
		while (y < circle.y + circle.radius)
		{
			if ((pow(x - circle.x, 2) + pow(y - circle.y, 2)) < pow(circle.radius, 2)
					&& x < image->width && y < image->height)
				mlx_put_pixel(image, x, y, circle.color);
			y++;
		}
		x++;
	}
	return 1;
}

int	draw_react(t_rect rect, mlx_image_t *image)
{
	double i;
	double j;
	// do border_with;

	// border_with = 0;
	i = rect.x;
	while (i <= rect.x + rect.side )
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
	double i;
	double j;

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

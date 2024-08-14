/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:46 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/13 09:53:28 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

float calc_fabs(double p_x, double p_y)
{
	if (p_x - p_y == 0)
		return (1);
	return (fabs(p_x - p_y));
}
double get_step(double dx, double dy)
{
	if (dx > dy)
		return (fabs(dx));
	return (fabs(dy));
}
int draw_line(t_line line, mlx_image_t *image)
{

	float dx;
	float x_inc;
	float dy;
	float y_inc;
	int i;

	dx = calc_fabs(line.p1.x, line.p2.x);
	dy = calc_fabs(line.p1.y, line.p2.y);
	x_inc = (line.p2.x - line.p1.x) / get_step(dx, dy);
	y_inc = (line.p2.y - line.p1.y) / get_step(dx, dy);
	i = 0;
	while (i <= get_step(dx, dy))
	{
		if (line.p1.x < image->width && line.p1.x >= 0 
			&& line.p1.y >= 0 && line.p1.y < image->height)
			mlx_put_pixel(image, line.p1.x, line.p1.y, line.color);
		line.p1.x += x_inc;
		line.p1.y += y_inc;
		i++;
	}
	return (1);
}

t_point new_point(double x, double y)
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

int draw_circle(t_circle circle, mlx_image_t *image)
{
	int x;
	int y;
	
	x = circle.x - circle.radius;
	while (x < circle.x + circle.radius)
	{
		y = circle.y - circle.radius;
		while (y < circle.y + circle.radius)
		{
			if ((pow(x - circle.x, 2) + pow(y - circle.y, 2)) < pow(circle.radius, 2))
				mlx_put_pixel(image, x, y, circle.color);
			y++;
		}
		x++;
	}
	return 1;
}

int draw_react(t_rect rect, mlx_image_t *image)
{
	double i;
	double j;

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

int draw_wall(t_wall wall, mlx_image_t *image)
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

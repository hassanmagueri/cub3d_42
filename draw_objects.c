/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:46 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/10 10:41:36 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

mlx_image_t	*draw_line(t_data *data, t_point p1, t_point p2, int color)
{
	mlx_image_t *line;
	int i;
	float dx = fabs(p1.x - p2.x);
	float dy = fabs(p1.y - p2.y);
	int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	float xinc = dx / (float)steps;
	float yinc = dy / (float)steps;

	i = 0;
	line = mlx_new_image(data->mlx, dx * dx, dy * dy);
	float X = p1.x;
	float Y = p1.y;

	for (int i = 0; i <= steps; i++)
	{
		printf("x: %f\n", X);
		printf("y: %f\n", Y);
		mlx_put_pixel(line, X, Y, color);
		X += xinc;
		Y += yinc;
	}
	return (line);
}

t_point	new_point(int x, int y)
{
	t_point p;

	p.x = x;
	p.y = y;
	return p;
}

mlx_image_t	*draw_circle(t_data *data, int radius, int color)
{
	mlx_image_t *circle;
	t_point center;
	int x;
	int y;

	center = new_point(radius, radius);
	circle = mlx_new_image(data->mlx, radius * 2, radius * 2);
	x = 0;
	while (x < (radius * 2))
	{
		y = 0;
		while (y < (radius * 2))
		{
			if ((pow(x - center.x, 2) + pow(y - center.y, 2)) <= pow(radius, 2))
				mlx_put_pixel(circle, x, y, color);
			y++;
		}
		x++;
	}
	return circle;
}

mlx_image_t	*draw_react(t_data *data, t_point p, int color)
{
	mlx_image_t *rect;
	int i;
	int j;

	i = 1;
	rect = mlx_new_image(data->mlx, p.width, p.height);
	while (i < p.height - 1)
	{
		j = 1;
		while (j < p.width - 1)
		{
			mlx_put_pixel(rect, j, i, color);
			j++;
		}
		i++;
	}
	return (rect);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:46 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/09 12:15:56 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

mlx_image_t	*draw_line(t_mlx *mlx, t_point p1, t_point p2, int color)
{
	mlx_image_t *line;
	int i;
	int dx = abs(p1.x - p2.x);
	int dy = abs(p1.y - p2.y);
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;

	i = 0;
	line = mlx_new_image(mlx->mlx, dx * dx / 2, dy * dy / 2 + 1);
	float X = p1.x;
	float Y = p1.y;
	for (int i = 0; i <= steps; i++)
	{
		mlx_put_pixel(line, X, Y, color);
		X += Xinc;
		Y += Yinc;
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

mlx_image_t	*draw_circle(t_mlx *mlx, int radius, int color)
{
	mlx_image_t *circle;
	t_point center;
	int x;
	int y;

	center = new_point(radius, radius);
	circle = mlx_new_image(mlx->mlx, radius * 2, radius * 2);
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

mlx_image_t	*draw_react(t_mlx *mlx, t_point p, int color)
{
	mlx_image_t *rect;
	int i;
	int j;

	i = 1;
	rect = mlx_new_image(mlx->mlx, p.width, p.height);
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

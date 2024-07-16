/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:30:52 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/15 14:27:16 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t		*clear_image(mlx_t *mlx, mlx_image_t *img)
{
	uint32_t	width;
	uint32_t	height;

	width = img->width;
	height = img->height;
	mlx_delete_image(mlx, img);
	// mlx_
	img = mlx_new_image(mlx, width, height);
	return (img);
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
t_rect new_rect(int x, int y, int side, int color)
{
	t_rect rect;

	rect.x = x;
	rect.y = y;
	rect.side = side;
	rect.color = color;
	return rect;
}

t_circle new_circle(int x, int y, int radius, int color)
{
	t_circle circle;

	circle.x = x;
	circle.y = y;
	circle.radius = radius;
	circle.color = color;
	return circle;
}

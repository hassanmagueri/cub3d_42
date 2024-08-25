/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_help_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:30:52 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/25 15:50:17 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

double	degtorad(int deg)
{
	return (deg * (M_PI / 180));
}

double	radtodeg(double rad)
{
	return (rad * (180 / M_PI));
}

int	low(int n1, int n2)
{
	if (n2 < n1)
		n1 = n2;
	return (n1);
}

int	xtoj(int x)
{
	int	j;

	j = x / TILE_SIZE;
	return (x / TILE_SIZE);
}

int	ytoi(int y)
{
	int	i;

	i = y / TILE_SIZE;
	return (y / TILE_SIZE);
}

t_line	new_line(t_point p1, t_point p2, int color)
{
	t_line	line;

	line.p1.x = p1.x;
	line.p1.y = p1.y;
	line.p2.x = p2.x;
	line.p2.y = p2.y;
	line.color = color;
	return (line);
}

int	ft_pixel(t_clr color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = color.red;
	g = color.green;
	b = color.blue;
	return (r << 24 | g << 16 | b << 8 | 255);
}

t_rect	new_rect(int x, int y, int side, int color)
{
	t_rect	rect;

	rect.x = x;
	rect.y = y;
	rect.side = side;
	rect.color = color;
	return (rect);
}

t_circle	new_circle(int x, int y, int radius, int color)
{
	t_circle	circle;

	circle.x = x;
	circle.y = y;
	circle.radius = radius;
	circle.color = color;
	return (circle);
}

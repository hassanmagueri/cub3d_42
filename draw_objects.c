/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:55:46 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/11 16:54:25 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int draw_line(t_data *data, t_point p1, t_point p2, int color, mlx_image_t *image)
{
	mlx_image_t *line;
	int i;
	float dx = fabs(p1.x - p2.x) == 0 ? 1 : fabs(p1.x - p2.x);
	float dy = fabs(p1.y - p2.y) == 0 ? 1: fabs(p1.y - p2.y);
	int steps = dx > dy ? fabs(dx) : fabs(dy);
	float xinc = (p1.x - p2.x) / steps;
	float yinc =  (p1.y - p2.y) / steps;

	i = 0;
	float X = p1.x;
	float Y = p1.y;

	for (int i = 0; i <= steps; i++)
	{
		mlx_put_pixel(image, X, Y, color);
		X += xinc;
		Y += yinc;
	}
	return (1);
}

// int draw_line(t_data *data, t_point p1, t_point p2, int color, mlx_image_t *image)
// {
// 	mlx_image_t *line;
// 	int i;
// 	float dx = fabs(p1.x - p2.x) == 0 ? 1 : fabs(p1.x - p2.x);
// 	float dy = fabs(p1.y - p2.y) == 0 ? 1: fabs(p1.y - p2.y);
// 	int steps = dx > dy ? fabs(dx) : fabs(dy);
// 	float xinc = dx / (float)steps;
// 	float yinc = dy / (float)steps;

// 	i = 0;
// 	float X = 0;
// 	float Y = 0;

// 	for (int i = 0; i <= steps; i++)
// 	{
// 		printf("x: %f, ", X);
// 		printf("y: %f\n", Y);
// 		mlx_put_pixel(image, X, Y, color);
// 		X += xinc;
// 		Y += yinc;
// 	}
// 	return (1);
// }



// mlx_image_t	*draw_line(t_data *data, t_point p1, t_point p2, int color)
// {
// 	mlx_image_t *line;
// 	int i;
// 	float dx = fabs(p1.x - p2.x) == 0 ? 1 : fabs(p1.x - p2.x);
// 	float dy = fabs(p1.y - p2.y) == 0 ? 1: fabs(p1.y - p2.y);
// 	int steps = dx > dy ? fabs(dx) : fabs(dy);
// 	float xinc = dx / (float)steps;
// 	float yinc = dy / (float)steps;

// 	i = 0;
// 	printf("dx: %f, dy: %f\n",dx, dy);
// 	line = mlx_new_image(data->mlx, (int)(dx * 3), (int)(dy * 3));
// 	if(line == NULL)
// 		return (printf("image load fail\n"), NULL);
// 	// float X = p1.x;
// 	// float Y = p1.y;
// 	float X = 0;
// 	float Y = 0;

// 	for (int i = 0; i <= steps; i++)
// 	{
// 		printf("x: %f, ", X);
// 		printf("y: %f\n", Y);
// 		mlx_put_pixel(line, X, Y, color);\
// 		printf("width: %d, height %d\n", line->width, line->height);
// 		X += xinc;
// 		Y += yinc;
// 	}
// 	return (line);
// }

t_point	new_point(int x, int y)
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

int	draw_circle(t_data *data, int radius, int color, mlx_image_t *image)
{
	mlx_image_t *circle;
	t_point center;
	int x;
	int y;

	center = new_point(image->width / 2, image->height / 2);
	set_background(image, BACKGROUND);
	x = center.x - radius;
	while (x < center.x + radius)
	{
		y = center.y - radius;
		while (y < center.y + radius)
		{
			if ((pow(x - center.x, 2) + pow(y - center.y, 2)) < pow(radius, 2))
				mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
	return 1;
}
// mlx_image_t	*draw_circle(t_data *data, int radius, int color)
// {
// 	mlx_image_t *circle;
// 	t_point center;
// 	int x;
// 	int y;

// 	center = new_point(radius, radius);
// 	circle = mlx_new_image(data->mlx, radius * 8, radius * 8);
// 	x = 0;
// 	while (x < (radius * 2))
// 	{
// 		y = 0;
// 		while (y < (radius * 2))
// 		{
// 			if ((pow(x - center.x, 2) + pow(y - center.y, 2)) < pow(radius, 2))
// 				mlx_put_pixel(circle, x, y, color);
// 			y++;
// 		}
// 		x++;
// 	}
// 	return circle;
// }

int	draw_react(t_data *data, t_point p, int color, mlx_image_t *image)
{
	int i;
	int j;

	i = 1;
	while (i < p.height - 1)
	{
		j = 1;
		while (j < p.width - 1)
		{
			mlx_put_pixel(image, j, i, color);
			j++;
		}
		i++;
	}
	return (1);
}
// mlx_image_t	*draw_react(t_data *data, t_point p, int color)
// {
// 	mlx_image_t *rect;
// 	int i;
// 	int j;

// 	i = 1;
// 	rect = mlx_new_image(data->mlx, p.width, p.height);
// 	while (i < p.height - 1)
// 	{
// 		j = 1;
// 		while (j < p.width - 1)
// 		{
// 			mlx_put_pixel(rect, j, i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (rect);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:30:52 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/29 19:47:07 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	draw_floor_ceiling(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->background_img->height / 2)
	{
		j = 0;
		while (j < data->background_img->width)
		{
			mlx_put_pixel(data->background_img, j, i, ft_pixel(data->ceiling));
			mlx_put_pixel(data->background_img, j,
				i + data->background_img->height / 2, ft_pixel(data->floor));
			j++;
		}
		i++;
	}
}

mlx_image_t	*reset_img(mlx_image_t *img)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < img->height)
			mlx_put_pixel(img, i, j++, 0);
		i++;
	}
	return (img);
}

int32_t	ft_pixel(t_clr color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	b = color.blue;
	r = color.red;
	g = color.green;
	return (r << 24 | g << 16 | b << 8 | 255);
}

t_point	new_point(double x, double y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:26:51 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/27 15:28:11 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	ray_distance(double dx, double dy)
{
	return (sqrt(pow(dx, 2) + pow(dy, 2)));
}

char	*swap_bytes(char *str)
{
	unsigned char	tmp;

	tmp = str[0];
	str[0] = str[3];
	str[3] = tmp;
	tmp = str[2];
	str[2] = str[1];
	str[1] = tmp;
	return (str);
}

void	ft_put_pixel( t_data *data, int y, uint32_t color)
{
	swap_bytes((char *)(&color));
	if (data->x_ray >= 0 && (size_t)data->x_ray < data->window_img->width
		&& y >= 0 && (size_t)y < data->window_img->height)
		mlx_put_pixel(data->window_img, data->x_ray, y, color);
}

int	painting_part_col(mlx_image_t *img, int start, int end, int x)
{
	int	y;

	y = start;
	while (y < end)
		mlx_put_pixel(img, x, y++, 0);
	return (0);
}

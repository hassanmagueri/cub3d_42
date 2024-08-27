/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:30:52 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/27 04:26:15 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

int	add_pixel(int direct)
{
	if (direct == -1)
		return (-1);
	return (0);
}

double	normalize_angle(double angle)
{
	double	res;

	res = fmod(angle, 2 * M_PI);
	if (res < 0)
		res += 2 * M_PI;
	return (res);
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

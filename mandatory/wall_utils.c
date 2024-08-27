/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:20:01 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/26 17:29:32 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	ret_offset_x(double wall_hit_x, double wall_hit_y,
		bool is_vr, mlx_texture_t *texture)
{
	int	offset_x;

	if (is_vr)
		offset_x = (int)wall_hit_y % texture->width;
	else
		offset_x = (int)wall_hit_x % texture->width;
	return (offset_x);
}

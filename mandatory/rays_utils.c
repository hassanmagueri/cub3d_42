/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 03:23:16 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/28 12:44:07 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

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

t_ray	low_ray(t_ray ver, t_ray hor)
{
	double	hyp_ver;
	double	hyp_hor;

	hyp_ver = pow(ver.dx, 2) + pow(ver.dy, 2);
	hyp_hor = pow(hor.dx, 2) + pow(hor.dy, 2);
	if (hyp_ver < hyp_hor)
		return (ver);
	return (hor);
}

bool	check_is_wall(t_map map, t_player player, double x, double y)
{
	char	**layout;
	size_t	i;
	size_t	j;

	x += player.x;
	y += player.y;
	layout = map.layout;
	i = (int)y / TILE_SIZE;
	j = (int)x / TILE_SIZE;
	if (i < 0 || j < 0 || i >= map.height || j >= map.width)
		return (false);
	if (layout[i][j] == '1' || layout[i][j] == 'C' )
		return (true);
	return (false);
}

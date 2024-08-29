/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 04:22:46 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/29 19:36:59 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

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

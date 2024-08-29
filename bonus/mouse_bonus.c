/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:51:31 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/29 14:12:52 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	move_mouse(double x_pos, double y_pos, void *arg)
{
	t_data	*data;
	double	x;

	(void) y_pos;
	data = (t_data *)arg;
	x = x_pos - (WINDOW_WIDTH / 2);
	data->player.rotation_angle += x * 0.0001;
	mlx_set_mouse_pos(data->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

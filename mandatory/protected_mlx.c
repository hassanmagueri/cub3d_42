/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:59:53 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/29 15:02:01 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	terminate_mlx(t_data *data)
{
	delete_texture(data->texture);
	delete_texture(data->textures.ea);
	delete_texture(data->textures.no);
	delete_texture(data->textures.so);
	delete_texture(data->textures.we);
	delete_image(data->mlx, data->background_img);
	delete_image(data->mlx, data->img);
	delete_image(data->mlx, data->window_img);
	mlx_terminate(data->mlx);
	ft_malloc(FREE, FREE);
	exit(EXIT_FAILURE);
}

void	set_mlx_vars_null(t_data *data)
{
	data->background_img = NULL;
	data->img = NULL;
	data->texture = NULL;
	data->textures = (t_textures){NULL, NULL, NULL, NULL};
	data->window_img = NULL;
}

void	init_vars(t_data *data)
{
	set_mlx_vars_null(data);
	data->textures.ea = load_png(data, data->es);
	data->textures.no = load_png(data, data->no);
	data->textures.so = load_png(data, data->so);
	data->textures.we = load_png(data, data->we);
	data->window_img = new_image(data, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->background_img = new_image(data, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void	image_to_window(t_data *data, mlx_image_t *img, int x, int y)
{
	int	res;

	res = mlx_image_to_window(data->mlx, img, x, y);
	if (res == -1)
		terminate_mlx(data);
}

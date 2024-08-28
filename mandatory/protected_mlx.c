/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:59:53 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/28 14:49:45 by emagueri         ###   ########.fr       */
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
	// ft_malloc(0, FREE);
	// save_imgs_texs(data, NULL, DELETE);
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
	data->textures.ea = load_png(data, data->EA);
	data->textures.no = load_png(data, data->NO);
	data->textures.so = load_png(data, data->SO);
	data->textures.we = load_png(data, data->WE);
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

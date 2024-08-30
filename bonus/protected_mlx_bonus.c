/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_mlx_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:59:53 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/29 21:35:17 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

void	terminate_mlx(t_data *data)
{
	delete_texture(data->tex_plr);
	delete_image(data->mlx, data->default_img);
	delete_texture(data->tex);
	delete_texture(data->tex_door);
	delete_texture(data->texture);
	delete_texture(data->textures.ea);
	delete_texture(data->textures.no);
	delete_texture(data->textures.so);
	delete_texture(data->textures.we);
	delete_image(data->mlx, data->minimap.img);
	delete_image(data->mlx, data->background_img);
	delete_image(data->mlx, data->img);
	delete_image(data->mlx, data->spr_img);
	delete_image(data->mlx, data->spr_img);
	delete_image(data->mlx, data->window_img);
	mlx_terminate(data->mlx);
	free_and_exit(data, NUM_IMAGES);
}

void	set_mlx_vars_null(t_data *data)
{
	data->minimap.img = NULL;
	data->background_img = NULL;
	data->default_img = NULL;
	data->img = NULL;
	data->spr_img = NULL;
	data->tex = NULL;
	data->tex_door = NULL;
	data->texture = NULL;
	data->tex_plr = NULL;
	data->textures = (t_textures){NULL, NULL, NULL, NULL};
	data->window_img = NULL;
}

void	init_vars(t_data *data)
{
	set_mlx_vars_null(data);
	data->textures.ea = load_png(data, data->ea);
	data->textures.no = load_png(data, data->no);
	data->textures.so = load_png(data, data->so);
	data->textures.we = load_png(data, data->we);
	data->tex_door = load_png(data, "./images/door_close.png");
	data->window_img = new_image(data, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->background_img = new_image(data, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->minimap.img = new_image(data, MINIMAP_HEIGHT * SCALE_SIZE,
			MINIMAP_WIDTH * SCALE_SIZE);
	data->tex_plr = load_png(data, "./sprite/Stechkin01.png");
	data->default_img = texture_to_image(data, data->tex_plr);
}

void	image_to_window(t_data *data, mlx_image_t *img, int x, int y)
{
	int	res;

	res = mlx_image_to_window(data->mlx, img, x, y);
	if (res == -1)
	{
		write(2, "Error\nfaild to image to window", 32);
		terminate_mlx(data);
	}
}

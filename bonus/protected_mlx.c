/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:59:53 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/25 16:03:43 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_bonus.h"

void	delete_image(mlx_t *mlx, mlx_image_t *img)
{
	if (img)
		mlx_delete_image(mlx, img);
}

void	delete_texture(mlx_texture_t *texture)
{
	if (texture)
		mlx_delete_texture(texture);
}

void	terminate_mlx(t_data *data)
{
	delete_texture(data->tex);
	delete_texture(data->tex_door);
	delete_texture(data->texture);
	delete_texture(data->tex_plr);
	delete_texture(data->textures.EA);
	delete_texture(data->textures.NO);
	delete_texture(data->textures.SO);
	delete_texture(data->textures.WE);
	delete_image(data->mlx, data->minimap.img);
	delete_image(data->mlx, data->background_img);
	delete_image(data->mlx, data->img);
	delete_image(data->mlx, data->spr_img);
	delete_image(data->mlx, data->spr_img);
	delete_image(data->mlx, data->window_img);
	mlx_terminate(data->mlx);
	exit(1);
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

mlx_texture_t	*load_png(t_data *data, char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (texture == NULL)
		terminate_mlx(data);
	return (texture);
}

mlx_image_t	*new_image(t_data *data, int width, int height)
{
	mlx_image_t	*img;

	img = mlx_new_image(data->mlx, width, height);
	if (img == NULL)
		terminate_mlx(data);
	return (img);
}

mlx_image_t	*texture_to_image(t_data *data, mlx_texture_t *texture)
{
	mlx_image_t	*img;

	if (texture == NULL)
		terminate_mlx(data);
	img = mlx_texture_to_image(data->mlx, texture);
	if (img == NULL)
		terminate_mlx(data);
	return (img);
}

void	init_vars(t_data *data)
{
	set_mlx_vars_null(data);
	data->textures.EA = load_png(data, data->EA);
	data->textures.NO = load_png(data, data->NO);
	data->textures.SO = load_png(data, data->SO);
	data->textures.WE = load_png(data, data->WE);
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
		terminate_mlx(data);
}

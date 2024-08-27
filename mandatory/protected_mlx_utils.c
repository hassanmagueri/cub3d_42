/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_mlx_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:59:53 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/27 16:52:01 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	delete_image(mlx_t *mlx, mlx_image_t *img)
{
	if (img)
		mlx_delete_image(mlx, img);
	img = NULL;
}

void	delete_texture(mlx_texture_t *texture)
{
	if (texture)
		mlx_delete_texture(texture);
	texture = NULL;
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

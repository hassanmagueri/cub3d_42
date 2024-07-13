/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:30:52 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/11 18:36:35 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t		*clear_image(mlx_t *mlx, mlx_image_t *img)
{
	uint32_t	width;
	uint32_t	height;

	width = img->width;
	height = img->height;
	mlx_delete_image(mlx, img);
	img = mlx_new_image(mlx, width, height);
	return (img);
}
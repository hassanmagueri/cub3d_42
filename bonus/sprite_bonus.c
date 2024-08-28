/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:43:21 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/28 17:50:38 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_strcpy(char *dest, char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

void	ft_strcut(char *dest, char *src)
{
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

void	load_and_display_image(t_data *data, int i)
{
	static mlx_image_t	*remove_img;

	if (remove_img)
		mlx_delete_image(data->mlx, remove_img);
	data->img = mlx_texture_to_image(data->mlx, data->sprite_textures[i]);
	if (!data->img)
		terminate_mlx(data);
	remove_img = data->img;
	mlx_image_to_window(data->mlx, data->img, 300, 300);
}

void	animation_sprite(void *arg)
{
	t_data		*data;
	static bool	is_pressed;
	static int	i;

	data = (t_data *)arg;
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	{
		delete_texture(data->tex_plr);
		delete_image(data->mlx, data->default_img);
		is_pressed = true;
		data->tex_plr = mlx_load_png("./sprite/Stechkin01.png");
		if (!data->tex_plr)
			terminate_mlx(data);
	}
	if (is_pressed)
	{
		load_and_display_image(data, i);
		i++;
	}
	if (i == NUM_IMAGES)
	{
		i = 0;
		is_pressed = false;
	}
}

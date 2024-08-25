/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:43:21 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/24 21:07:20 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


void ft_put_image(t_data *data, mlx_image_t *img)
{
	mlx_image_to_window(data->mlx, img, 300, 300);
}
void ft_strcpy(char *dest, char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}
void ft_strcut(char *dest, char *src)
{
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}
void load_and_display_image(t_data *data, int i)
{
	static mlx_image_t *remove_img;
	char path[100];
	char index[10];
	char png[10];

	if (remove_img)
		mlx_delete_image(data->mlx, remove_img);
	ft_strcpy(path, "./sprite/StechkinEx");
	ft_strcpy(index, ft_itoa(i + 1));
	ft_strcut(path, index);
	ft_strcut(path, ".png");
	data->tex = mlx_load_png(path);
	data->img = mlx_texture_to_image(data->mlx, data->tex);
	remove_img = data->img;
	ft_put_image(data, data->img);
}
void animation_sprite(void *arg)
{
	t_data *data;
	static bool is_pressed;
	static int i;

	data = (t_data *)arg;
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	{
		mlx_delete_image(data->mlx, data->default_img);
		is_pressed = true;
		data->tex_plr = mlx_load_png("./sprite/Stechkin01.png");
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

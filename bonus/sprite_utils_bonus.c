/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:55:29 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/28 20:53:21 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_and_exit(t_data *data, int i)
{
	while (--i >= 0)
		mlx_delete_texture((mlx_texture_t *)data->sprite_textures[i]);
	free(data->sprite_textures);
	ft_malloc(FREE, FREE);
	exit(EXIT_FAILURE);
}

void	init_sprites(t_data *data)
{
	char	path[100];
	char	index[10];
	int		i;

	i = 0;
	data->sprite_textures = (void **)malloc(sizeof(void *) * (NUM_IMAGES + 1));
	if (!data->sprite_textures)
		ft_putendl_fd_color("Error\nmalloc failure", 2, RED_E);
	while (i < NUM_IMAGES)
	{
		ft_strcpy(path, "./sprite/StechkinEx");
		ft_strcpy(index, ft_itoa(i + 1));
		ft_strcut(path, index);
		ft_strcut(path, ".png");
		data->tex = mlx_load_png(path);
		if (!data->tex)
			free_and_exit(data, i);
		data->sprite_textures[i] = data->tex;
		i++;
	}
	data->sprite_textures[i] = NULL;
}

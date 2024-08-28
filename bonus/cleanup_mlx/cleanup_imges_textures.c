/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_imges_textures.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:46:14 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/27 21:23:13 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

t_sprite	*create_node(void *adrress, t_status status)
{
	t_sprite	*node;

	node = malloc(sizeof(t_sprite));
	if (!node)
		return (NULL);
	node->address = adrress;
	node->status = status;
	node->next = NULL;
	return (node);
}

void	addback(t_sprite **head, t_sprite *new)
{
	t_sprite	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	save_imgs_texs(t_data *data, void *address, t_status status)
{
	static t_sprite	*head;
	t_sprite		*new;

	new = create_node(address, status);
	if (!new)
		ft_putendl_fd_color("Error\nFailed to create node", 2, RED_E);
	if (status == TEXTURE || status == IMAGE)
		addback(&head, new);
	else if (status == DELETE)
	{
		while (head)
		{
			if (head->status == TEXTURE)
				mlx_delete_texture((mlx_texture_t *)head->address);
			else if (head->status == IMAGE)
				mlx_delete_image(data->mlx, (mlx_image_t *)head->address);
			head = head->next;
		}
		head = NULL;
	}
}

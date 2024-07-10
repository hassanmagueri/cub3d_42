/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:51:11 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/10 10:23:17 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double degtorad(int deg)
{
    return deg * (M_PI / 180);
}

void new_player(t_data *data, t_point p, mlx_image_t *img)
{
    t_player player;

    player = data->player;
    data->player.x = p.x;
    data->player.y = p.y;
    data->player.angle = M_PI / 2;
    data->player.rotation_angle = 0;
    data->player.rotation_speed = 3;
    data->player.walk_direction = 0;
    data->player.move_speed = 3;
    data->player.vector_len = TILE_SIZE ;
    data->player.img = img;
    // create_vector_player(data);
}

int create_vector_player(t_data *data)
{
    t_player *player = &(data->player);
    t_point p2;

    printf("player angle: %f\n", player->angle);
    printf("player x: %d\n", player->x);
    p2 = new_point(
        player->x + cos(player->angle) * 20,
        player->y + sin(player->angle) * 20
    );
    printf("(x: %d, y: %d)\n", p2.x, p2.y);
    draw_line(data, new_point(player->x, player->y), p2, 0x000000FF);
    return 1;
}


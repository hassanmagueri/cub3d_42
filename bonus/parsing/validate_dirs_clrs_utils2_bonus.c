/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_dirs_clrs_utils2_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:17:30 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/27 16:18:10 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	check_newline(char **map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		if (!map[y][0])
			ft_putendl_fd_color("Error\nInvalid map", 2, RED_E);
		y++;
	}
}

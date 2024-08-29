/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_dirs_clrs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:53:09 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/29 13:48:08 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_is_number(char *clr)
{
	int	i;

	i = 0;
	while (clr[i])
	{
		if (!ft_isdigit(clr[i]))
			return (-1);
		i++;
	}
	return (0);
}

void	validate_color(char *clr)
{
	char	**out;
	char	*line;
	int		i;

	line = ft_strtrim(clr + 1, " ");
	if (check_comma(line))
	{
		ft_malloc(0, FREE);
		ft_putendl_fd_color("Error\nInvalid color", 2, RED_E);
	}
	out = ft_split(line, ',');
	i = 0;
	while (out[i])
	{
		if (check_is_number(out[i]) || ft_atoi(out[i]) > 255)
			(ft_malloc(0, FREE), print_error("Error\nInvalid color"));
		i++;
	}
	if (i != 3)
		(ft_malloc(0, FREE), print_error("Error\nInvalid color"));
}

int	get_len_dirs(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	validate_all_dirs(t_data *data)
{
	char	**out;
	char	*line;
	int		i;

	i = 0;
	while (data->dirs[i])
	{
		out = ft_split(data->dirs[i], ' ');
		line = ft_strtrim(data->dirs[i], " ");
		if (line[2] != ' ' || get_len_dirs(out) != 2)
		{
			ft_malloc(0, FREE);
			ft_putendl_fd_color("Error\nInvalid directions", 2, RED_E);
		}
		i++;
	}
}

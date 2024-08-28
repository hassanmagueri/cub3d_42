/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_data_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:38:32 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/28 15:25:51 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	count_empty_lines(char **map_data, int max_count)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (map_data[i] && count < max_count)
	{	
		if (skip_spaces(map_data[i]))
		{
			i++;
			continue ;
		}
		if (map_data[i][0])
			count++;
		i++;
	}
	while (map_data[i] && !map_data[i][0])
		i++;
	return (i);
}

char	*remove_new_line(char *line)
{
	char	*new_ret;
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	new_ret = (char *)ft_malloc(i + 1, ALLOC);
	if (!new_ret)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		new_ret[i] = line[i];
		i++;
	}
	new_ret[i] = '\0';
	return (new_ret);
}

char	*get_first_char(char *line)
{
	char	*new_ret;
	int		i;
	int		j;

	j = 0;
	new_ret = (char *)ft_malloc(sizeof(char) * 2, ALLOC);
	if (!new_ret)
		ft_putendl_fd_color("Error\nmalloc failure", 2, RED_E);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	new_ret[0] = line[i];
	new_ret[1] = '\0';
	return (new_ret);
}

char	*get_two_char(char *line)
{
	char	*re_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	re_line = ft_malloc(3, ALLOC);
	if (!re_line)
		ft_putendl_fd_color("Error\nmalloc failure", 2, RED_E);
	while (line[i] && line[i] == ' ')
		i++;
	while (j < 2 && line[i])
		re_line[j++] = line[i++];
	re_line[j] = '\0';
	return (re_line);
}

void	set_top_map(t_data *data)
{
	int	i;
	int	j;
	int	z;

	((1) && (i = 0, j = 0, z = 0));
	data->dirs = (char **)ft_malloc(sizeof(char *) * 5, ALLOC);
	data->clrs = (char **)ft_malloc(sizeof(char *) * 3, ALLOC);
	while (data->top_map[i])
	{
		if (is_direction(get_two_char(data->top_map[i])))
			data->dirs[j++] = data->top_map[i];
		else if (is_color(get_first_char(data->top_map[i])))
			data->clrs[z++] = data->top_map[i];
		i++;
	}
	data->dirs[j] = NULL;
	data->clrs[z] = NULL;
}	

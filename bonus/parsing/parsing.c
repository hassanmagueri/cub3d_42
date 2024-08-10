/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:28:47 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/09 10:35:37 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
void ft_putendl_fd_color(char *s, int fd, char *color)
{
	write(fd, color, 5);
	ft_putendl_fd(s, fd);
	write(fd, "\033[0m", 4);
}
char *remove_new_line(char *line)
{
	int i;
	i = 0;
	char *new_ret;
	while (line[i] && line[i] != '\n')
		i++;
	new_ret = (char *)malloc(i + 1);
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
char *get_first_char(char *line)
{
	int i;
	int j;
	char *new_ret;

	j = 0;
	new_ret = (char *)malloc(sizeof(char) * 2);
	if (!new_ret)
		ft_putendl_fd_color("Error\nmalloc failure", 2, RED_E);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	new_ret[0] = line[i];
	new_ret[1] = '\0';
	return (new_ret);
}
char *get_two_char(char *line)
{
	int i = 0;
	int j = 0;
	char *re_line = malloc(3);
	if (!re_line)
		ft_putendl_fd_color("Error\nmalloc failure", 2, RED_E);
	while (line[i] && line[i] == ' ')
		i++;
	while (j < 2 && line[i])
		re_line[j++] = line[i++];
	re_line[j] = '\0';
	return (re_line);
}
bool check_dirs(char *line, char *to_find)
{
	if (ft_strcmp(get_two_char(line), to_find))
		return (false);
	return (true);
}
bool check_color(char *line, char *to_find)
{
	if (ft_strcmp(get_first_char(line), to_find))
		return (false);
	return (true);
}
int find_colors(char **data)
{
	int i;
	bool check_clr_f;
	bool check_clr_c;

	check_clr_f = false;
	check_clr_c = false;
	i = 0;
	while (data[i])
	{
		if (check_color(data[i], "F"))
			check_clr_f = true;
		if (check_color(data[i], "C"))
			check_clr_c = true;
		i++;
	}
	if (!check_clr_f || !check_clr_c)
		return (-1);
	return (0);
}
int find_dirs(char **data)
{
	bool check_no;
	bool check_so;
	bool check_we;
	bool check_ea;
	int i;

	(1) && (check_no = false, check_so = false,
			check_we = false, check_ea = false);
	i = 0;
	while (data[i])
	{
		int j = 0;
		char *line = data[i];
		while (line[j] && line[j] == ' ')
			j++;
		if (check_dirs(line + j, "NO"))
			check_no = true;
		else if (check_dirs(line + j, "SO"))
			check_so = true;
		else if (check_dirs(line + j, "WE"))
			check_we = true;
		else if (check_dirs(line + j, "EA"))
			check_ea = true;
		i++;
	}
	if (!check_no || !check_so || !check_we || !check_ea)
		return (-1);
	return (0);
}
void validate_top_map(t_data *data)
{
	int fd;
	int fd1;
	char *two_chr;
	char *line;

	char **top_map = (char **)malloc(sizeof(char *) * 7);
	if (!top_map)
		ft_putendl_fd_color("Error\nmalloc failure", 2, RED_E);
	fd = open(FILE, O_RDONLY);
	printf("image path %s\n", FILE);
	if (fd < 0)
		ft_putendl_fd_color("Error\nOpen failure", 2, RED_E);
	int i = 0;
	int j = 0;
	while (data->map_data[i])
	{
		if (data->map_data[i][0])
			top_map[j++] = data->map_data[i];
		i++;
		if (j == 6)
			break;
	}
	top_map[j] = NULL;
	if (find_colors(top_map))
		ft_putendl_fd_color("Error\nInvalid top map", 2, RED_E);
	if (find_dirs(top_map))
		ft_putendl_fd_color("Error\nInvalid top map", 2, RED_E);
}
int get_count_map(t_data *data, int i)
{
	int count;

	count = 0;
	while (data->map_data[i])
	{
		count++;
		i++;
	}
	return (count);
}
void set_map(t_data *data)
{
	int i;
	int j;
	char *line;

	data->dirs = (char **)malloc(sizeof(char *) * 5);
	data->clrs = (char **)malloc(sizeof(char *) * 3);
	if (!data->clrs)
		ft_putendl_fd_color("Error\n malloc failure", 2, RED_E);
	if (!data->dirs)
		ft_putendl_fd_color("Error\n malloc failure", 2, RED_E);
	int fd = open(FILE, O_RDONLY);
	if (fd < 0)
		ft_putendl_fd_color("Error\nopen failure", 2, RED_E);
	i = 0;
	j = 0;
	int z = 0;
	while (data->map_data[i])
	{
		char *two_chr = get_two_char(data->map_data[i]);
		char *first_chr = get_first_char(data->map_data[i]);
		if (!ft_strcmp(two_chr, "NO") || !ft_strcmp(two_chr, "SO") || !ft_strcmp(two_chr, "WE") || !ft_strcmp(two_chr, "EA"))
			data->dirs[j++] = data->map_data[i];
		else if (!ft_strcmp(first_chr, "F") || !ft_strcmp(first_chr, "C"))
			data->clrs[z++] = data->map_data[i];
		i++;
	}
	data->dirs[j] = NULL;
	data->clrs[z] = NULL;
	i = 0;
	j = 0;
	while (data->map_data[i])
	{
		line = data->map_data[i];
		if (line[0])
			j++;
		i++;
		if (j == 6)
			break;
	}
	while (!data->map_data[i][0])
		i++;
	int count = get_count_map(data, i);
	data->map.layout = (char **)malloc(sizeof(char *) * (count + 1));
	if (!data->map.layout)
		ft_putendl_fd_color("Error\nmalloc failure", 2, RED_E);
	j = 0;
	while (data->map_data[i])
	{
		data->map.layout[j++] = data->map_data[i];
		i++;
	}
	data->map.layout[j] = NULL;
}
void load_map_data(t_data *data)
{
	int fd;
	char *line;

	fd = open(FILE, O_RDONLY, 0666);
	if (fd < 0)
		ft_putendl_fd_color("Error\nOpen failure", 2, RED_E);
	line = get_next_line(fd);
	int count = 0;
	while (line)
	{
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(FILE, O_RDONLY, 0666);
	if (fd < 0)
		ft_putendl_fd_color("Error\nOpen failure", 2, RED_E);
	data->map_data = (char **)malloc(sizeof(char *) * (count + 1));
	if (!data->map_data)
		ft_putendl_fd_color("Error\nmalloc failure", 2, RED_E);
	int i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		data->map_data[i++] = remove_new_line(line);
		line = get_next_line(fd);
	}
	data->map_data[i] = NULL;
}

int get_len_dirs(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
void validate_all_dirs(t_data *data)
{
	int i;
	char **out;

	i = 0;
	while (data->dirs[i])
	{
		out = ft_split(data->dirs[i], ' ');
		if (!out)
			ft_putendl_fd_color("Error\nmalloc failure", 2, RED_E);
		if (get_len_dirs(out) != 2)
			ft_putendl_fd_color("Error\nInvalid directions", 2, RED_E);
		i++;
	}
	i = 0;
	while (data->dirs[i])
	{
		int j = 0;
		while (data->dirs[i][j] && data->dirs[i][j] == ' ')
			j++;
		j += 2;
		if (data->dirs[i][j] != ' ')
			ft_putendl_fd_color("Error\nInvalid directions", 2, RED_E);

		i++;
	}
}
char *get_util_comma(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ',')
		i++;

	return (ft_substr(line, 0, i));
}
int get_count_comma(char *clr)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (clr[i])
	{
		if (clr[i] == ',')
			count++;
		i++;
	}
	return (++count);
}
int check_comma(char *clr)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (clr[i])
	{
		if (clr[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (-1);
	return (0);
}
int check_is_number(char *clr)
{
	int i;

	clr = ft_strtrim(clr, " ");
	i = 0;
	while (clr[i])
	{
		if (!ft_isdigit(clr[i]))
			return (-1);
		i++;
	}
	return (0);
}
void validate_color(char *clr)
{
	int i;
	char *line;

	line = ft_strtrim(clr + 1, " ");
	if (check_comma(line))
		ft_putendl_fd_color("Error\nInvalid color", 2, RED_E);
	char **out = ft_split(line, ',');
	i = 0;
	while (out[i])
	{
		if (check_is_number(out[i]))
			ft_putendl_fd_color("Error\nInvalid color", 2, RED_E);
		i++;
	}
	i = 0;
	while (out[i])
	{
		if (ft_atoi(out[i]) > 255)
			ft_putendl_fd_color("Error\nInvalid color (value > 255)", 2, RED_E);
		i++;
	}
}
void validate_colors(t_data *data)
{
	int i;
	char *clr;

	i = 0;
	while (data->clrs[i])
	{
		int j = 0;
		clr = ft_strtrim(data->clrs[i], " ");
		if (clr[j + 1] != ' ')
			ft_putendl_fd_color("Error\nInvalid colors", 2, RED_E);
		i++;
	}
	i = 0;
	while (data->clrs[i])
	{
		clr = ft_strtrim(data->clrs[i], " ");
		validate_color(clr);
		i++;
	}
}
int validate_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
			return (-1);
		i++;
	}
	return (0);
}
int get_len_map(t_data *data)
{
	int i;

	i = 0;
	while (data->map.layout[i])
		i++;
	return (i);
}
int validate_char(char chr)
{
	if (chr == '0' || chr == 'N' || chr == 'S' || chr == 'W' || chr == 'E')
		return (-1);
	return (0);
}
void parse_map(t_data *data)
{
	int i;
	char *line;
	int lg_line;
	int to_find;

	if (validate_line(data->map.layout[0]))
		ft_putendl_fd_color("Error\nInvalid character", 2, RED_E);
	if (validate_line(data->map.layout[get_len_map(data) - 1]))
		ft_putendl_fd_color("Error\nInvalid character", 2, RED_E);
	i = 0;
	while (data->map.layout[i])
	{
		if (data->map.layout[i][0])
			line = ft_strtrim(data->map.layout[i], " ");
		if (validate_char(line[0]))
			ft_putendl_fd_color("Error\nInvalid character", 2, RED_E);
		if (validate_char(line[ft_strlen(line) - 1]))
			ft_putendl_fd_color("Error\nInvalid character", 2, RED_E);
		i++;
	}

	i = 0;
	to_find = 0;
	lg_line = ft_strlen(data->map.layout[i]);
	while (data->map.layout[i])
	{
		int current_length = ft_strlen(data->map.layout[i]);
		if (lg_line < current_length)
		{
			to_find = i;
			lg_line = current_length;
		}
		i++;
	}

	int len = ft_strlen(data->map.layout[to_find]);
	int length = len;
	i = 0;
	while (data->map.layout[i])
	{
		int j = 0;
		len = length;
		char *line = (char *)malloc(sizeof(char) * (length + 1));
		while (data->map.layout[i][j])
		{

			if (data->map.layout[i][j] == ' ')
				line[j] = '$';
			else
				line[j] = data->map.layout[i][j];

			j++;
		}
		len = len - j;
		while (len--)
		{
			line[j++] = '$';
		}
		line[j] = '\0';
		data->map.layout[i] = line;
		i++;
	}
	int x = 0;
	int y = 0;
	while (data->map.layout[y])
	{
		x = 0;
		while (data->map.layout[y][x])
		{
			if (data->map.layout[y][x] == '0')
			{
				if (data->map.layout[y][x + 1] == '$' || data->map.layout[y][x - 1] == '$' || data->map.layout[y + 1][x] == '$' || data->map.layout[y - 1][x] == '$')
					ft_putendl_fd_color("Error\nInvalid map - adjacent to '0' is a space", 2, RED_E);
			}
			x++;
		}
		y++;
	}
	x = 0;
	y = 0;
	int count = 0;
	while (data->map.layout[y])
	{
		x = 0;
		while (data->map.layout[y][x])
		{
			if (data->map.layout[y][x] != '$' && data->map.layout[y][x] != '0' && data->map.layout[y][x] != '1' && data->map.layout[y][x] != 'C' && data->map.layout[y][x] != 'O' && data->map.layout[y][x] != 'N' && data->map.layout[y][x] != 'S' && data->map.layout[y][x] != 'E' && data->map.layout[y][x] != 'W')
				ft_putendl_fd_color("Error\nInvalid character in map", 2, RED_E);
			if (data->map.layout[y][x] == 'N' || data->map.layout[y][x] == 'S' || data->map.layout[y][x] == 'W' || data->map.layout[y][x] == 'E')
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		ft_putendl_fd_color("Error\nMap must contain exactly one start position ('N', 'S', 'E', or 'W')", 2, RED_E);
	y = 0;
	while (data->map.layout[y])
	{
		x = 0;
		while (data->map.layout[y][x])
		{
			if (data->map.layout[y][x] == 'N' || data->map.layout[y][x] == 'S' || data->map.layout[y][x] == 'E' || data->map.layout[y][x] == 'W')
			{
				if (data->map.layout[y][x + 1] == '$' || data->map.layout[y][x - 1] == '$' || data->map.layout[y + 1][x] == '$' || data->map.layout[y - 1][x] == '$')
					ft_putendl_fd_color("Error\nSpace is not surrounded by '1'", 2, RED_E);
			}
			x++;
		}
		y++;
	}
	y = 0;
	while (data->map.layout[y])
		y++;
	data->map.width = ft_strlen(data->map.layout[0]);
	data->map.height = y;
}
void init_clrs_dirs(t_data *data)
{
	int i;

	i = 0;
	data->floor.red = 0;
	data->floor.green = 0;
	data->floor.blue = 0;
	while (data->dirs[i])
	{
		char **out = ft_split(data->dirs[i], ' ');
		if (!out)
			ft_putendl_fd_color("Error\nmalloc failure", 2, RED_E);
		if (!ft_strcmp(out[0], "NO"))
			data->NO = out[1];
		else if (!ft_strcmp(out[0], "SO"))
			data->SO = out[1];
		else if (!ft_strcmp(out[0], "WE"))
			data->WE = out[1];
		else
			data->EA = out[1];
		i++;
	}
	i = 0;
	while (data->clrs[i])
	{
		char *clr = ft_strtrim(data->clrs[i], " ");
		if (clr[ft_strlen(clr) - 1] == ',')
			ft_putendl_fd_color("Error\nInvalid colors", 2, RED_E);
		char **clrs = ft_split(clr + 1, ',');
		if (clr[0] == 'F')
		{
			data->floor.red = ft_atoi(clrs[0]);
			data->floor.green = ft_atoi(clrs[1]);
			data->floor.blue = ft_atoi(clrs[2]);
		}
		else if (clr[0] == 'C')
		{
			data->ceiling.red = ft_atoi(clrs[0]);
			data->ceiling.green = ft_atoi(clrs[1]);
			data->ceiling.blue = ft_atoi(clrs[2]);
		}
		i++;
	}
}
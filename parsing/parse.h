/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:12:02 by belguabd          #+#    #+#             */
/*   Updated: 2024/07/21 16:38:18 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include "read_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#ifndef COLORS_H
#define COLORS_H
#define RED_E "\033[31m"
#include "../cub3d.h"
#endif
typedef struct t_colors
{
    int red;
    int green;
    int blue;
} t_clr;

typedef struct data
{
    double turn_direction;
    double walk_direction;
    double radius;
    double rotation_angle;
    double move_speed;
    double rotation_speed;

    double x;
    double y;
    double p_x;
    double p_y;
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    char **map_data;
    char **dirs;
    char **clrs;
    char **map;
    t_clr floor;
    t_clr ceiling;
    mlx_t *mlx;
    mlx_image_t *img;
} t_data_p;

int ft_strcmp(char *str1, char *str2);
size_t ft_strlcat(char *dst, const char *src, size_t dstsize);
void ft_putendl_fd(char *s, int fd);
char **ft_split(char const *s, char c);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strtrim(char const *s1, char const *set);
int ft_atoi(const char *str);
int ft_isdigit(int c);

void load_map_data(t_data_p *data);
void validate_top_map(t_data_p *data);
void set_map(t_data_p *data);
void validate_all_dirs(t_data_p *data);
void validate_colors(t_data_p *data);
void parse_map(t_data_p *data);
void init_clrs_dirs(t_data_p *data);
#endif
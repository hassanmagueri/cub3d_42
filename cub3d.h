/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:59:38 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/01 22:25:20 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include "MLX42.h"
#include "utils/get_next_line/get_next_line.h"

#define TILE_SIZE 8
#define BACKGROUND 0xFD42EE55

#define WIDTH 3000
#define HEIGHT 1200

#define DEG 0
#define P_RAD TILE_SIZE / 7
#define ROT_SPEED 5
#define MOVE_SPEED 3

#define NUM_RAYS WIDTH
#define FOV 60 * (M_PI / 180)
#define RAY_RAD 1000

// ============= define colors ===========
#define BLACK	0x000000FF
#define WHITE	0xFFFFFFFF
#define RED		0xFF0000FF
#define LIME	0x00FF00FF
#define BLUE	0x0000FFFF
#define YELLOW	0xFFFF00FF
#define CYAN	0x00FFFFFF
#define MAGENTA	0xFF00FFFF

// Shades of grey with full opacity
#define DARK_GREY 0x404040FF
#define GREY 0x808080FF
#define LIGHT_GREY 0xC0C0C0FF

// Semi-transparent colors (50% opacity)
#define SEMI_BLACK 0x00000080
#define SEMI_WHITE 0xFFFFFF80
#define SEMI_RED 0xFF000080
#define SEMI_LIME 0x00FF0080
#define SEMI_BLUE 0x0000FF80
#define SEMI_YELLOW 0xFFFF0080
#define SEMI_CYAN 0x00FFFF80
#define SEMI_MAGENTA 0xFF00FF80

#ifndef COLORS_H
#define COLORS_H
#define RED_E "\033[31m"
#endif



typedef struct t_colors
{
	int red;
	int green;
	int blue;
} t_clr;
typedef struct s_point
{
	double x;
	double y;
} t_point;

typedef struct s_rect
{
	double x;
	double y;
	int side; // maybe this is the problem
	int color;
} t_rect;

typedef struct s_wall
{
	double	x;
	double	y;
	double	width;
	double	height;
	int		color;
} t_wall;

typedef struct s_line
{
	t_point p1;
	t_point p2;
	int color;
} t_line;

typedef struct s_circle
{
	int x;
	int y;
	int radius;
	int color;
} t_circle;

typedef struct s_ray
{
	double	dx;
	double	dy;
	double	angle;
	bool	is_vr;
	short	direct;
} t_ray;

typedef struct s_player
{
	double x;
	double y;
	double angle;
	double rotation_angle; // -1 1
	int rotation_speed;
	int walk_direction; // -1 1
	int move_speed;
	mlx_image_t *img;
	int radius;
} t_player;

typedef struct s_map
{
	size_t	width;
	size_t	height;
	char	**layout;
} t_map;

typedef struct s_data
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char **map_data;
	char **dirs;
	char **clrs;
	// char **map;
	// int width;
	// int height;
	t_map map;
	t_clr floor;
	t_clr ceiling;
	mlx_t		*mlx;
	t_player	player;
	mlx_image_t	*player_img;
	t_ray rays[NUM_RAYS];
} t_data;
// ===================== functions parsing =====================
int ft_strcmp(char *str1, char *str2);
size_t ft_strlcat(char *dst, const char *src, size_t dstsize);
void ft_putendl_fd(char *s, int fd);
char **ft_split(char const *s, char c);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strtrim(char const *s1, char const *set);
int ft_atoi(const char *str);
int ft_isdigit(int c);
void load_map_data(t_data *data);
void validate_top_map(t_data *data);
void set_map(t_data *data);
void validate_all_dirs(t_data *data);
void validate_colors(t_data *data);
void parse_map(t_data *data);
void init_clrs_dirs(t_data *data);
// ===================== draw objects =====================
t_point new_point(double x, double y);
t_rect new_rect(int x, int y, int side, int color);
t_circle new_circle(int x, int y, int radius, int color);
t_line new_line(t_point p1, t_point p2, int color);
int draw_circle(t_circle circle, mlx_image_t *image);
int draw_line(t_line line, mlx_image_t *image);
int draw_react(t_rect rect, mlx_image_t *image);
int	draw_wall(t_wall wall, mlx_image_t *image);

// ================== player object ==================
t_player new_player(t_data *data, int x, int y);
int draw_player(t_data *data);
int create_vector_player(t_data *data);
int update_player(t_data *data);

// ================== mlx assisted ==================
mlx_image_t *clear_image(mlx_t *mlx, mlx_image_t *img);
double degtorad(int deg);
double radtodeg(double rad);
mlx_image_t *new_image_to_window(mlx_t *mlx, int width, int height);

// ================== ray functions ==================
int new_ray(t_data *data, double ray_angle);
int cast_rays(t_map map, t_player player , t_ray (*rays)[NUM_RAYS]);
// bool is_wall(t_map map, int x, int y);
bool	is_wall(t_data *data, int x, int y);

t_ray horizontal_ray(t_player player, t_map map, double ray_angle);
t_ray vertical_ray(t_player player, t_map map, double ray_angle);

// ================== walls functions ==================
void project_walls(t_data *data);

#endif

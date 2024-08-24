/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:59:38 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/24 13:47:47 by emagueri         ###   ########.fr       */
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
#include <math.h>
#include <stdbool.h>
#include <sys/fcntl.h>
#include "./MLX/MLX42.h"
#include "utils/get_next_line/get_next_line_bonus.h"

#define TILE_SIZE 1024
#define SCALE 0.02
#define BACKGROUND 0xFD42EE55
#define SCALE_SIZE (TILE_SIZE * SCALE)

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 1000

#define DEG 90
#define P_RAD 4
#define ROT_SPEED 10
#define MOVE_SPEED 70

#define MINIMAP_WIDTH 11
#define MINIMAP_HEIGHT 11

#define NUM_RAYS WINDOW_WIDTH
#define FOV 60 * (M_PI / 180)

// ============= define colors ===========
#define BLACK 0x000000FF
#define WHITE 0xFFFFFFFF
#define RED 0xFF0000FF
#define LIME 0x00FF00FF
#define BLUE 0x0000FFFF
#define YELLOW 0xFFFF00FF
#define CYAN 0x00FFFFFF
#define MAGENTA 0xFF00FFFF

// Shades of grey with full opacity
#define GREY 0x808080FF
#define DARK_GREY 0x404040FF
#define LIGHT_GREY 0xC0C0C0FF

// Semi-transparent colors (50% opacity)
#define SEMI_GREY		0x808080AA
#define SEMI_RED		0xFF000080
#define SEMI_LIME		0x00FF0080
#define SEMI_BLUE		0x0000FF80
#define SEMI_CYAN		0x00FFFF80
#define SEMI_BLACK		0x00000080
#define SEMI_WHITE		0xFFFFFF40
#define SEMI_YELLOW		0xFFFF0060
#define SEMI_MAGENTA	0xFF00FF80

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
	double x;
	double y;
	double width;
	double height;
	int color;
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
	double dx;
	double dy;
	double angle;
	bool is_vr;
	short direct;
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


typedef struct s_index
{
	int i;
	int j;
}t_index;


typedef struct s_map
{
	size_t width;
	size_t height;
	char **layout;
} t_map;

typedef struct s_textures
{
	mlx_texture_t *NO;
	mlx_texture_t *SO;
	mlx_texture_t *WE;
	mlx_texture_t *EA;
} t_textures;

typedef struct s_minimap
{
	t_point start_p;
	t_point player_p;
	t_point pn;
	mlx_image_t *img;
}t_minimap;


typedef struct s_data
{
	int d_x;
	int d_y;
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char **map_data;
	char **dirs;
	char **clrs;
	t_map map;
	t_clr floor;
	t_clr ceiling;
	mlx_t *mlx;
	t_ray rays[NUM_RAYS];
	t_player player;
	t_textures textures;
	mlx_image_t *player_img;
	mlx_image_t *window_img;
	mlx_image_t *background_img;
	mlx_texture_t *texture;
	mlx_image_t *spr_img;
	mlx_image_t *default_img;
	mlx_texture_t *tex_plr;
	mlx_texture_t *tex_door;
	t_minimap minimap;
	int x_ray;
	int dist_door;
	bool  check_door;
	char wall_door;
	int x_door;
	int y_door;
	int place_x;
	int place_y;
	bool is_c;
	double angle_mouse;
	char **top_map;
	char *map_path;
	
	
} t_data;
// ===================== functions utils =====================
char *ft_itoa(int n);
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
int draw_wall(t_wall wall, mlx_image_t *image);

// ================== player object ==================
t_player new_player(t_data *data, int x, int y, int angle);
int draw_player(t_data *data);
int create_vector_player(t_data *data);
int update_player(t_data *data);

// ================== mlx assisted ==================
mlx_image_t *clear_image(mlx_t *mlx, mlx_image_t *img);
double degtorad(int deg);
double radtodeg(double rad);
mlx_image_t *new_image_to_window(mlx_t *mlx, int width, int height);
mlx_image_t *reset_img(mlx_image_t *img);
int32_t ft_pixel(t_clr color);

// ================== ray functions ==================
int new_ray(t_data *data, double ray_angle);
int cast_rays(t_data *data, t_map map, t_player player, t_ray (*rays)[NUM_RAYS]);
// bool is_wall(t_map map, int x, int y);
bool is_wall(t_data *data, int x, int y);

t_ray horizontal_ray(t_player player, t_map map, double ray_angle);
t_ray vertical_ray(t_player player, t_map map, double ray_angle);

// ================== walls functions ==================
void project_walls(t_data *data, t_ray ray, int x);
int update_player(t_data *data);
// ================== minimap functions ==================
int draw_minimap(t_data *data);
void	ft_putendl_fd_color(char *s, int fd, char *color);
int	count_lines(t_data *data);
char	*remove_new_line(char *line);
bool	is_direction(const char *str);
bool	is_color(const char *str);
bool	check_dirs(char *line, char *to_find);
bool	check_character(char c);
void	print_error(char *message);
int	find_longest_line_index(t_data *data);
void	validate_map(t_data *data);
int	check_comma(char *clr);
char	*get_two_char(char *line);
int	get_len_map(t_data *data);
int	find_colors(char **data);
int	find_dirs(char **data);
void	validate_colors(t_data *data);
void	validate_color(char *clr);
char	*get_first_char(char *line);
void	set_top_map(t_data *data);
int	count_empty_lines(char **map_data, int max_count);
int	get_count_map(t_data *data, int i);
void doors(t_data *data , t_map map);
#endif
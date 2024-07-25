/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:59:38 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/25 18:34:26 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include "MLX42.h"

# define TILE_SIZE 8
# define BACKGROUND 0xFD42EE55

# define WIDTH  2000
# define HEIGHT 1000

# define DEG 90
# define P_RAD 8
# define ROT_SPEED 3
# define MOVE_SPEED 3

# define NUM_RAYS 1000
# define FOV 60 * (M_PI / 180)
# define RAY_RAD 1

// ============= define colors ===========
# define BLACK         0x000000FF
# define WHITE         0xFFFFFFFF
# define RED           0xFF0000FF
# define LIME          0x00FF00FF
# define BLUE          0x0000FFFF
# define YELLOW        0xFFFF00FF
# define CYAN          0x00FFFFFF
# define MAGENTA       0xFF00FFFF

// Shades of grey with full opacity
# define DARK_GREY     0x404040FF
# define GREY          0x808080FF
# define LIGHT_GREY    0xC0C0C0FF

// Semi-transparent colors (50% opacity)
# define SEMI_BLACK    0x00000080
# define SEMI_WHITE    0xFFFFFF80
# define SEMI_RED      0xFF000080
# define SEMI_LIME     0x00FF0080
# define SEMI_BLUE     0x0000FF80
# define SEMI_YELLOW   0xFFFF0080
# define SEMI_CYAN     0x00FFFF80
# define SEMI_MAGENTA  0xFF00FF80

typedef struct s_point
{
	double	x;
	double	y;
} t_point;

typedef struct s_map
{
	
} t_map;

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
} t_ray;


typedef struct s_player
{
	double	x;
	double	y;
	double angle;
	double rotation_angle; // -1 1
	int rotation_speed;
	int walk_direction;// -1 1
	int move_speed;
	mlx_image_t *img;
	int radius;
} t_player;
typedef struct s_data
{
	char		(*grid)[14];
	mlx_t		*mlx;
	t_ray		rays[NUM_RAYS];
	t_player	player;
	mlx_image_t	*player_img;
} t_data;

// ===================== draw objects =====================
t_point		new_point(double x, double y);
t_rect		new_rect(int x, int y, int side, int color);
t_circle	new_circle(int x, int y, int radius, int color);
t_line		new_line(t_point p1,t_point p2, int color);
int			draw_circle(t_circle circle, mlx_image_t *image);
int			draw_line(t_line line, mlx_image_t *image);
int			draw_react(t_rect rect, mlx_image_t *image);
int			draw_wall(t_wall wall, mlx_image_t *image);

// ================== player object ==================
t_player	new_player(t_data *data, int x, int y);
int			draw_player(t_data *data);
int			create_vector_player(t_data *data);
int			update_player(t_data *data);

// ================== mlx assisted ==================
mlx_image_t		*clear_image(mlx_t *mlx, mlx_image_t *img);
mlx_image_t		*new_image_to_window(mlx_t *mlx, int width, int height);
double			degtorad(int deg);
double			radtodeg(double rad);

// ================== ray functions ==================
int		cast_rays(char (*map)[14], t_player player, t_ray (*rays_ref)[NUM_RAYS]);
bool	is_wall(char (*map)[14], int x, int y);
double	ray_distance(double dx, double dy);
t_ray	horizontal_ray(t_player player, char (*map)[14], double ray_angle);
t_ray	vertical_ray(t_player player, char (*map)[14], double ray_angle);

// ================== walls 3D  ==================
void project_walls(t_data *data);

#endif


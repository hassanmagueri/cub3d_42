/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:59:38 by emagueri          #+#    #+#             */
/*   Updated: 2024/07/14 10:23:36 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include "MLX42.h"

# define TILE_SIZE 64
# define DEG 90
# define BACKGROUND 0xFD42EE55
# define WIDTH  TILE_SIZE * 14
# define HEIGHT TILE_SIZE * 12

typedef struct s_point
{
	double x;
	double y;
	int width;
	int height;
} t_point;

typedef struct s_map
{
	
} t_map;

typedef struct s_rect
{
	int x;
	int y;
	int side;
	int color;
}t_rect;

typedef struct s_circle
{
	int x;
	int y;
	int radius;
	int color;
}t_circle;


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
	// int			;
	mlx_t		*mlx;
	t_player	player;
	mlx_image_t	*player_img;
} t_data;

// ===================== draw objects =====================
t_point		new_point(double x, double y);
t_rect		new_rect(int x, int y, int side, int color);
t_circle	new_circle(int x, int y, int radius, int color);
int			draw_circle(t_circle circle, mlx_image_t *image);
int			draw_line(t_data *data, t_point p1, t_point p2, int color, mlx_image_t *image);
int			draw_react(t_rect rect, mlx_image_t *image);

// ================== player object ==================
t_player	new_player(t_data *data, int x, int y);
int			draw_player(t_data *data, t_point point_image);
int			create_vector_player(t_data *data);
int			update_player(t_data *data);

// ================== mlx assisted ==================
mlx_image_t		*clear_image(mlx_t *mlx, mlx_image_t *img);
double degtorad(int deg);
double radtodeg(double rad);


#endif


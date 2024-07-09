
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "MLX42.h"

#define TILE_SIZE 64
#define WIDTH  TILE_SIZE * 14
#define HEIGHT TILE_SIZE * 12

typedef struct s_point
{
	int x;
	int y;
	int width;
	int height;
} t_point;

typedef struct s_map
{

} t_map;

typedef struct s_player
{
	int x;
	int y;
	int angle;
	
} t_player;
typedef struct s_mlx
{
	mlx_t *mlx;
	char (*grid)[14];
	mlx_image_t *player;
} t_mlx;

// ===================== draw objects =====================
t_point		new_point(int x, int y);
mlx_image_t	*draw_circle(t_mlx *mlx, int radius, int color);
mlx_image_t	*draw_line(t_mlx *mlx, t_point p1, t_point p2, int color);
mlx_image_t	*draw_circle(t_mlx *mlx, int radius, int color);
mlx_image_t	*draw_react(t_mlx *mlx, t_point p, int color);

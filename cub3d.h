
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
	float x;
	float y;
	int width;
	int height;
} t_point;

typedef struct s_map
{

} t_map;


typedef struct s_player
{
	int	x;
	int	y;
	double angle;
	int rotation_angle; // -1 1
	int rotation_speed;
	int walk_direction;// -1 1
	int move_speed;
	mlx_image_t *img;
	int vector_len;
} t_player;
typedef struct s_data
{
	mlx_t *mlx;
	char (*grid)[14];
	mlx_image_t *player_img;
	t_player player;
} t_data;

// ===================== draw objects =====================
t_point		new_point(int x, int y);
mlx_image_t	*draw_circle(t_data *data, int radius, int color);
mlx_image_t	*draw_line(t_data *data, t_point p1, t_point p2, int color);
mlx_image_t	*draw_circle(t_data *data, int radius, int color);
mlx_image_t	*draw_react(t_data *data, t_point p, int color);

// ================== player object ==================
void	new_player(t_data *data, t_point p, mlx_image_t *img);
int		create_vector_player(t_data *data);
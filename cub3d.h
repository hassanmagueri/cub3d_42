
#include <stdio.h>
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


typedef struct s_mlx
{
    mlx_t *mlx;
    char (*grid)[14];
} t_mlx;




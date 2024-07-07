// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "cub3d.h"

static mlx_image_t *image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void *param)
{
	(void)param;
	int n;
	n = 40;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		n = 40;
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				n % 0xFF, // R
				n % 0xFF, // G
				n % 0xFF, // B
				n % 0xFF  // A
			);
			n += 1;
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void *param)
{
	mlx_t *mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	// if (mlx_is_key_down(mlx, MLX_KEY_UP))
	// 	image->instances[0].y -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	// 	image->instances[0].y += 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	// 	image->instances[0].x -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	// 	image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

mlx_image_t *create_react(t_mlx *mlx, t_point p, int (*color)(int, int, int, int))
{
	mlx_image_t *rect;
	int i;
	int j;

	i = 1;
	rect = mlx_new_image(mlx->mlx, p.width, p.height);
	while (i < p.height - 1)
	{
		j = 1;
		while (j < p.width - 1)
		{
			mlx_put_pixel(rect, j, i, color(0xFF, 0xFF, 0xFF, 0xFF));
			j++;
		}
		i++;
	}
	return rect;
}

int32_t main(void)
{
	t_mlx mlx;
	char grid[][14] =
		{
			"11111111111111",
			"10110001111111",
			"10110001010011",
			"10110001010011",
			"10110101010011",
			"10110001010011",
			"10110001010011",
			"10110101010011",
			"10110001010011",
			"10110101010011",
			"10110101010011",
			"11111111111111"
		};
	mlx.grid = grid;

	printf("%c\n", mlx.grid[0][0]);
	mlx.mlx = mlx_init(WIDTH * 2, HEIGHT * 2, "cub3D", false);
	t_point p;
	p.x = 0;
	p.y = 0;
	p.width = TILE_SIZE;
	p.height = TILE_SIZE;
	mlx_image_t *rect = create_react(&mlx, p, ft_pixel);
	int i, j;
	i = 0;
	while (i < 12)
	{
		j = 0;
		while (j < 14)
		{
			if (mlx.grid[i][j] == '1')
				mlx_image_to_window(mlx.mlx, rect, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}

	// image = mlx_new_image(mlx.mlx, TILE_SIZE, TILE_SIZE);
	// mlx_image_to_window(mlx.mlx, image, 0, 0);
	// mlx_put_pixel(image, 0, 0, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF));
	// mlx_loop_hook(mlx.mlx, ft_randomize, mlx.mlx);
	mlx_loop_hook(mlx.mlx, ft_hook, mlx.mlx);

	mlx_loop(mlx.mlx);
	mlx_terminate(mlx.mlx);
	return (EXIT_SUCCESS);
}
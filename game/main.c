#include "../cub3d.h"
#define TILE 50
void handle_key(mlx_key_data_t keydata, void *param)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        mlx_close_window((mlx_t *)param);
    }
}

void draw_rectangle(mlx_image_t *img, int x, int y, int color)
{
    for (int i = 0; i < TILE - 1; ++i)
    {
        for (int j = 0; j < TILE - 1; ++j)
        {
            mlx_put_pixel(img, x + i, y + j, color);
        }
    }
}
void ft_circle(mlx_image_t *img, int x0, int y0, int radius, int color)
{
    for (int x = -radius; x <= radius; ++x)
    {
        for (int y = -radius; y <= radius; ++y)
        {
            if (x * x + y * y <= radius * radius)
            {
                mlx_put_pixel(img, x0 + x, y0 + y, color);
            }
        }
    }
}
int main(void)
{
    char map[][16] =
        {
            "1111111111111111",
            "1000000100000001",
            "1011101111000001",
            "1010001011000001",
            "1010000011000001",
            "1010000011000001",
            "1010100011000001",
            "1010100011000001",
            "1011101111000001",
            "10000000N0000001",
            "1110111111000001",
            "1110111111000001",
            "1000000000000001",
            "1110011111000001",
            "1100000111110001",
            "1111111111111111"};

    mlx_t *mlx = mlx_init(800, 800, "My MLX Window", true);

    mlx_image_t *img = mlx_new_image(mlx, 800, 800);
    mlx_image_to_window(mlx, img, 0, 0);
    int y = 0;
    while (y < 16)
    {
        int x = 0;
        while (x < 16)
        {
            if (map[y][x] == '1')
            {
                draw_rectangle(img, x * TILE, y * TILE, WHITE);
            }
            else if (map[y][x] == '0')
                draw_rectangle(img, x * TILE, y * TILE, BLACK);
            else if (map[y][x] == 'N')
            {
                ft_circle(img, x * TILE, y * TILE, 20, RED);
            }

            x++;
        }
        y++;
    }
    mlx_key_hook(mlx, &handle_key, mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}

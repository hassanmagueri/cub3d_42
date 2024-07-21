#include "../cub3d.h"
#include <math.h>
#define TILE_P 15
#define TILE_G 50
#define FOV_ANGLE 60.0
#define NUM_RAYE 400
void draw_rectangle(t_data_p *data, int p_x, int p_y, int color)
{
    int y;
    int x;

    y = 0;
    while (y < TILE_G)
    {
        x = 0;
        while (x < TILE_G)
        {
            mlx_put_pixel(data->img, x + p_x, y + p_y, color);
            x++;
        }
        y++;
    }
}
void draw_line_plyr(t_data_p *data, int x1, int y1, int x2, int y2, int color)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    double xInc = dx / (float)steps;
    double yInc = dy / (float)steps;

    double x = x1;
    double y = y1;
    for (int i = 0; i <= steps; i++)
    {
        if (x < data->img->width && x >= 0 && y < data->img->height && y >= 0)
            mlx_put_pixel(data->img, (int)x, (int)y, RED);
        x += xInc;
        y += yInc;
    }
}

void draw_circle_plr(t_data_p *data)
{
    double x, y;
    double r = TILE_P / 2.0;
    double x_p = data->p_x;
    double y_p = data->p_y;
    y = y_p - r;

    while (y < y_p + r)
    {
        x = x_p - r;
        while (x < x_p + r)
        {
            if ((pow((x - x_p), 2) + pow((y - y_p), 2)) < pow(r, 2))
                mlx_put_pixel(data->img, x, y, RED);
            x++;
        }
        y++;
    }
}
void display_map(t_data_p *data)
{

    for (size_t i = 0; data->map[i]; i++)
    {
        printf("%s\n", data->map[i]);
    }
}
double degrees_to_radians(double degrees)
{
    return degrees * (M_PI / 180.0);
}
bool check_is_wall(t_data_p *data, double x, double y)
{
    int new_y = y / TILE_G;
    int new_x = x / TILE_G;
    if (data->map[new_y][new_x] == '0')
        return (true);
    return (false);
}
void draw_plyr(t_data_p *data)
{

    double angle = 40 * M_PI / 180;
    data->rotation_angle += data->turn_direction * data->rotation_speed;
    double speed = data->move_speed * data->walk_direction;
    double new_px = data->p_x + cos(data->rotation_angle) * speed;
    double new_py = data->p_y + sin(data->rotation_angle) * speed;
    if (check_is_wall(data, new_px, new_py))
    {
        data->p_x = new_px;
        data->p_y = new_py;
    }
    draw_circle_plr(data);
    draw_line_plyr(data, data->p_x, data->p_y, data->p_x + cos(data->rotation_angle) * 100, data->p_y + sin(data->rotation_angle) * 100, RED);
    angle = data->rotation_angle - degrees_to_radians(FOV_ANGLE / 2.0);

    int i = 0;
    while (i < NUM_RAYE)
    {
        draw_line_plyr(data, data->p_x, data->p_y, data->p_x + cos(angle) * 100, data->p_y + sin(angle) * 100, RED);
        angle += degrees_to_radians(FOV_ANGLE / NUM_RAYE);
        i++;
    }
    data->walk_direction = 0;
    data->turn_direction = 0;
}

void draw_map(t_data_p *data)
{
    int y;
    int x;

    y = 0;
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == '1')
                draw_rectangle(data, x * TILE_G, y * TILE_G, WHITE);
            if (data->map[y][x] == '0')
                draw_rectangle(data, x * TILE_G, y * TILE_G, BLACK);
            x++;
        }
        y++;
    }
    draw_plyr(data);
}
void handle_key(void *arg)
{
    t_data_p *data = (t_data_p *)arg;
    if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
        data->turn_direction = 1;
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
        data->turn_direction = -1;
    if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
        data->walk_direction = 1;
    if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
        data->walk_direction = -1;
    draw_map(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
    data->map[1][1] = '0';
}
void find_pos_plyr(t_data_p *data)
{
    int y;
    int x;
    y = 0;
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == 'N')
            {
                data->p_x = (x * TILE_G) + (TILE_G / 2);
                data->p_y = (y * TILE_G) + (TILE_G / 2);
                data->map[y][x] = '0';
                return;
            }
            x++;
        }
        y++;
    }
}
void init_data(t_data_p *data)
{
    data->radius = 3;
    data->turn_direction = 0;
    data->walk_direction = 0;
    data->move_speed = 3;
    data->rotation_angle = M_PI / 2;
    data->rotation_speed = 2 * (M_PI / 180);
    find_pos_plyr(data);
}
int main()
{
    t_data_p data;

    load_map_data(&data);
    load_map_data(&data);
    validate_top_map(&data);
    set_map(&data);
    validate_all_dirs(&data);
    validate_colors(&data);
    parse_map(&data);
    init_clrs_dirs(&data);
    data.mlx = mlx_init(800, 800, "My MLX Window", true);
    data.img = mlx_new_image(data.mlx, 800, 800);
    mlx_image_to_window(data.mlx, data.img, 0, 0);
    init_data(&data);

    data.x = 0;
    data.y = 0;
    draw_map(&data);
    mlx_loop_hook(data.mlx, handle_key, &data);
    mlx_loop(data.mlx);
    mlx_terminate(data.mlx);

    
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:59:38 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/29 18:34:27 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include "./MLX/.MLX42.h"
# include "./utils/get_next_line/get_next_line.h"

# define RED_E "\033[31m"

# define TILE_SIZE 1024
# define SCALE 0.02
# define SCALE_SIZE 20.4

# define DBL_MAX 1.7976931348623157e+308

# define WINDOW_WIDTH 1500
# define WINDOW_HEIGHT 1000

# define FREE 0
# define ALLOC 1

# define DEG 90
# define P_RAD 4
# define ROT_SPEED 10
# define MOVE_SPEED 220

# define NUM_RAYS WINDOW_WIDTH
# define FOV 1.0471975512
# define RAY_RAD 1000

// ============= define colors ===========
# define BLACK 0x000000FF
# define WHITE 0xFFFFFFFF
# define RED 0xFF0000FF
# define LIME 0x00FF00FF
# define BLUE 0x0000FFFF
# define YELLOW 0xFFFF00FF
# define CYAN 0x00FFFFFF
# define MAGENTA 0xFF00FFFF

// Shades of grey with full opacity
# define GREY 0x808080FF
# define DARK_GREY 0x404040FF
# define LIGHT_GREY 0xC0C0C0FF

// Semi-transparent colors (50% opacity)
# define SEMI_RED 0xFF000080
# define SEMI_LIME 0x00FF0080
# define SEMI_BLUE 0x0000FF80
# define SEMI_CYAN 0x00FFFF80
# define SEMI_BLACK 0x00000080
# define SEMI_WHITE 0xFFFFFF80
# define SEMI_YELLOW 0xFFFF0080
# define SEMI_MAGENTA 0xFF00FF80

typedef struct s_splt
{
	char	**res;
	int		i;
	int		j;
	int		to_find;
}	t_splt;

typedef struct s_mem_mgr
{
	void				*address;
	struct s_mem_mgr	*next;
}	t_free;

typedef struct t_colors
{
	int	red;
	int	green;
	int	blue;
}	t_clr;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_rect
{
	int		side;
	int		color;
	double	x;
	double	y;
}	t_rect;

typedef struct s_wall
{
	double	x;
	double	y;
	double	width;
	double	height;
	int		color;
}	t_wall;

typedef struct s_line
{
	int		color;
	t_point	p1;
	t_point	p2;
}	t_line;

typedef struct s_circle
{
	int	x;
	int	y;
	int	radius;
	int	color;
}	t_circle;

typedef struct s_ray
{
	double	dx;
	double	dy;
	double	angle;
	bool	is_vr;
	short	direct;
}	t_ray;

typedef struct s_player
{
	int			radius;
	int			rotation_speed;
	int			walk_direction;
	int			move_speed;
	double		x;
	double		y;
	double		angle;
	double		rotation_angle;
	mlx_image_t	*img;
}	t_player;

typedef struct s_map
{
	size_t	width;
	size_t	height;
	char	**layout;
}	t_map;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_textures;

typedef struct s_data
{
	int				x_ray;
	int				offsetx;
	char			*no;
	char			*so;
	char			*we;
	char			*es;
	char			**map_data;
	char			**dirs;
	char			**clrs;
	char			*map_path;
	char			**top_map;
	double			wall_height;
	mlx_t			*mlx;
	uint32_t		*p_clrs;
	t_ray			rays[NUM_RAYS];
	t_map			map;
	t_clr			floor;
	t_clr			ceiling;
	t_player		player;
	t_textures		textures;
	mlx_image_t		*player_img;
	mlx_image_t		*window_img;
	mlx_image_t		*background_img;
	mlx_image_t		*img;
	mlx_texture_t	*texture;
}	t_data;

// ===================== functions parsing =====================

int				ft_strcmp(const char *str1, char *str2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
void			ft_putendl_fd(char *s, int fd);
void			load_map_data(t_data *data);
void			validate_top_map(t_data *data);
void			set_map(t_data *data);
void			validate_all_dirs(t_data *data);
void			validate_colors(t_data *data);
void			validate_color(char *clr);
void			parse_map(t_data *data);
void			init_clrs_dirs(t_data *data);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
// =========	============ draw objects =====================
int				draw_circle(t_circle circle, mlx_image_t *image);
int				draw_line(t_line line, mlx_image_t *image);
int				draw_react(t_rect rect, mlx_image_t *image);
int				draw_wall(t_wall wall, mlx_image_t *image);
t_point			new_point(double x, double y);
t_rect			new_rect(int x, int y, int side, int color);
t_circle		new_circle(int x, int y, int radius, int color);
t_line			new_line(t_point p1, t_point p2, int color);

// =========	========= player object ==================
t_player		new_player(t_data *data, int x, int y, int angle);
int				draw_player(t_data *data);
int				create_vector_player(t_data *data);
int				update_player(t_data *data);

// =========	========= mlx assisted ==================
void			draw_floor_ceiling(t_data *data);
void			set_player(t_data *data, char *map, int i);
double			degtorad(int deg);
double			radtodeg(double rad);
int32_t			ft_pixel(t_clr color);
mlx_image_t		*clear_image(mlx_t *mlx, mlx_image_t *img);
mlx_image_t		*new_image_to_window(mlx_t *mlx, int width, int height);
mlx_image_t		*reset_img(mlx_image_t *img);

// =========	========= ray functions ==================
int				new_ray(t_data *data, double ray_angle);
int				cast_rays(t_data *data, t_map map, t_player player,
					t_ray (*rays)[NUM_RAYS]);
int				add_pixel(int direct);
bool			is_wall(t_data *data, int x, int y);
t_ray			low_ray(t_ray ver, t_ray hor);
bool			check_is_wall(t_map map, t_player player, double x, double y);
t_ray			horizontal_ray(t_player player, t_map map, double ray_angle);
t_ray			vertical_ray(t_player player, t_map map, double ray_angle);
double			normalize_angle(double angle);

// ================== walls functions ==================
void			project_walls(t_data *data, t_ray ray, int x);

// ================== protected function ==================

void			init_vars(t_data *data);
void			delete_image(mlx_t *mlx, mlx_image_t *img);
void			delete_texture(mlx_texture_t *texture);
void			terminate_mlx(t_data *data);
void			set_mlx_vars_null(t_data *data);
void			image_to_window(t_data *data, mlx_image_t *img, int x, int y);
mlx_image_t		*new_image(t_data *data, int width, int height);
mlx_image_t		*texture_to_image(t_data *data, mlx_texture_t *texture);
mlx_texture_t	*load_png(t_data *data, char *path);

// ================== protected function ==================

void			init_vars(t_data *data);
void			delete_image(mlx_t *mlx, mlx_image_t *img);
void			delete_texture(mlx_texture_t *texture);
void			terminate_mlx(t_data *data);
void			set_mlx_vars_null(t_data *data);
void			image_to_window(t_data *data, mlx_image_t *img, int x, int y);
mlx_image_t		*new_image(t_data *data, int width, int height);
mlx_image_t		*texture_to_image(t_data *data, mlx_texture_t *texture);
mlx_texture_t	*load_png(t_data *data, char *path);

// ================== parsing functions ==================
int				count_lines(t_data *data);
int				find_longest_line_index(t_data *data);
int				check_comma(char *clr);
int				get_len_map(t_data *data);
int				find_colors(char **data);
int				find_dirs(char **data);
int				count_empty_lines(char **map_data, int max_count);
int				get_count_map(t_data *data, int i);
int				ret_offset_x(double wall_hit_x,
					double wall_hit_y, bool is_vr, mlx_texture_t *texture);
bool			is_direction(const char *str);
bool			is_color(const char *str);
bool			check_dirs(char *line, char *to_find);
bool			check_character(char c);
void			validate_map(t_data *data);
char			*remove_new_line(char *line);
char			*get_two_char(char *line);
char			*swap_bytes(char *str);
char			*get_first_char(char *line);
void			ft_putendl_fd_color(char *s, int fd, char *color);
void			print_error(char *message);
void			set_top_map(t_data *data);
void			*ft_malloc(size_t size, int status);
void			check_newline(char **map);
double			ray_distance(double dx, double dy);
bool			skip_spaces(char *line);
#endif

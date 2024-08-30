/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 04:42:49 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/30 16:58:33 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <math.h>
# include <stdbool.h>
# include <sys/fcntl.h>
# include "MLX42.h"
# include "utils/get_next_line/get_next_line_bonus.h"

# define RED_E "\033[31m"

# define TILE_SIZE 1024
# define SCALE 0.02
# define SCALE_SIZE 20.4

# define DBL_MAX 1.7976931348623157e+308

# define WINDOW_WIDTH 1800
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
# define NUM_IMAGES 68

# define MINIMAP_WIDTH 11
# define MINIMAP_HEIGHT 11

# define ALLOC 1
# define FREE 0

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
# define SEMI_GREY 0x808080AA
# define SEMI_RED 0xFF000080
# define SEMI_LIME 0x00FF0080
# define SEMI_BLUE 0x0000FF80
# define SEMI_CYAN 0x00FFFF80
# define SEMI_BLACK 0x00000080
# define SEMI_DARK 0x40404080
# define SEMI_WHITE 0xFFFFFF80
# define SEMI_YELLOW 0xFFFF00A0
# define SEMI_MAGENTA 0xFF00FF80

typedef struct s_mem_mgr
{
	void				*address;
	struct s_mem_mgr	*next;
}	t_free;

typedef struct s_splt
{
	char	**res;
	int		i;
	int		j;
	int		to_find;
}	t_splt;

typedef enum e_status
{
	TEXTURE,
	IMAGE,
	DELETE
}	t_status;

typedef struct s_sprite
{
	void			*address;
	t_status		status;
	struct cleanup	*next;
}	t_delete;

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
	double	x;
	double	y;
	int		side; // maybe this is the problem
	int		color;
}	t_rect;

typedef struct s_wall
{
	int		color;
	double	x;
	double	y;
	double	width;
	double	height;
}	t_wall;

typedef struct s_line
{
	t_point		p1;
	t_point		p2;
	int			color;
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
	int		is_vr;
	short	direct;
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	rotation_angle; // -1 1
	int		rotation_speed;
	int		walk_direction; // -1 1
	int		move_speed;
	int		radius;
}	t_player;

typedef struct s_index
{
	int	i;
	int	j;
}	t_index;

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

typedef struct s_minimap
{
	t_point			start_p;
	t_point			player_p;
	t_point			pn;
	mlx_image_t		*img;
}	t_minimap;

typedef struct s_data
{
	int				d_x;
	int				d_y;
	int				x_ray;
	int				dist_door;
	int				x_door;
	int				y_door;
	int				place_x;
	int				place_y;
	int				offsetx;
	bool			check_door;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			**map_data;
	char			**dirs;
	char			**clrs;
	char			wall_door;
	char			**top_map;
	char			*map_path;
	void			**sprite_textures;
	double			angle_mouse;
	double			wall_height;
	uint32_t		*p_clrs;
	t_map			map;
	t_clr			floor;
	t_clr			ceiling;
	mlx_t			*mlx;
	t_ray			rays[NUM_RAYS];
	t_player		player;
	t_minimap		minimap;
	t_textures		textures;
	mlx_image_t		*window_img;
	mlx_image_t		*background_img;
	mlx_image_t		*spr_img;
	mlx_image_t		*default_img;
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	mlx_texture_t	*tex_plr;
	mlx_texture_t	*tex_door;
	mlx_texture_t	*tex;
}	t_data;

// ===================== functions utils =====================

int				ft_strcmp(char *str1, char *str2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
char			*ft_itoa(int n);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
void			ft_putendl_fd(char *s, int fd);
void			ft_strcut(char *dest, char *src);
void			ft_strcpy(char *dest, char *src);
bool			skip_spaces(char *line);

// ===================== functions parsing =====================

void			load_map_data(t_data *data);
void			validate_top_map(t_data *data);
void			set_map(t_data *data);
void			validate_all_dirs(t_data *data);
void			validate_colors(t_data *data);
void			parse_map(t_data *data);
void			init_clrs_dirs(t_data *data);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);

// ===================== draw objects =====================

int				painting_background(mlx_image_t *img,
					t_clr ceiling, t_clr floor);
int				draw_circle(t_circle circle, mlx_image_t *image);
int				draw_line(t_line line, mlx_image_t *image);
int				draw_react(t_rect rect, mlx_image_t *image);
int				draw_wall(t_wall wall, mlx_image_t *image);
t_line			new_line(t_point p1, t_point p2, int color);
t_rect			new_rect(int x, int y, int side, int color);
t_circle		new_circle(int x, int y, int radius, int color);
t_point			new_point(double x, double y);

// ================== player object ==================
int				draw_player(t_data *data);
int				update_player(t_data *data);
int				create_vector_player(t_data *data);
void			set_player_direction(t_data *data, t_index index);
t_player		new_player(t_data *data, int x, int y, int angle);

// ================== mlx assisted ==================
int				add_pixel(int direct);
double			degtorad(int deg);
double			radtodeg(double rad);
double			normalize_angle(double angle);
int32_t			ft_pixel(t_clr color);
mlx_image_t		*clear_image(mlx_t *mlx, mlx_image_t *img);
mlx_image_t		*new_image_to_window(mlx_t *mlx, int width, int height);
mlx_image_t		*reset_img(mlx_image_t *img);

// ================== ray functions ==================

int				new_ray(t_data *data, double ray_angle);
int				cast_rays(t_data *data, t_map map, t_player player,
					t_ray (*rays)[NUM_RAYS]);
bool			is_wall(t_data *data, int x, int y);
bool			check_is_wall(t_map map, t_player player, double x, double y);
t_ray			horizontal_ray(t_player player, t_map map, double ray_angle);
t_ray			vertical_ray(t_player player, t_map map, double ray_angle);
t_ray			low_ray(t_ray ver, t_ray hor);

// ================== walls functions ==================
void			project_walls(t_data *data, t_ray ray, int x);
int				update_player(t_data *data);
double			ray_distance(double dx, double dy);
// ================== minimap functions ==================
int				draw_minimap(t_data *data);
int				draw_react_minimap(t_rect rect, mlx_image_t *image,
					int width, int height);
int				reset_minimap(mlx_image_t *img, t_circle c);
bool			is_out(int i_scale, int j_scale, t_map map);
int				set_rays(mlx_image_t *img, t_ray rays[NUM_RAYS]);
int				border_minimap(mlx_image_t *img, t_circle c);
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

// ================== brahim ==================
int				count_lines(t_data *data);
int				find_longest_line_index(t_data *data);
int				check_comma(char *clr);
int				find_colors(char **data);
int				find_dirs(char **data);
int				count_empty_lines(char **map_data, int max_count);
int				get_count_map(t_data *data, int i);
int				painting_part_col(mlx_image_t *img, int start, int end, int x);
int				get_len_map(t_data *data);
void			ft_putendl_fd_color(char *s, int fd, char *color);
void			print_error(char *message);
void			validate_map(t_data *data);
void			validate_color(char *clr);
void			validate_colors(t_data *data);
void			set_top_map(t_data *data);
void			doors(t_data *data, t_map map);
void			parsing_doors(t_data *data);
void			animation_sprite(void *arg);
void			*ft_malloc(size_t size, int status);
void			save_imgs_texs(t_data *data, void *adrress, t_status status);
void			move_mouse(double x_pos, double y_pos, void *arg);
void			ft_put_pixel( t_data *data, int y, uint32_t color);
void			check_newline(char **map);
char			*remove_new_line(char *line);
char			*get_two_char(char *line);
char			*get_first_char(char *line);
bool			is_direction(char *str);
bool			is_color(char *str);
bool			check_dirs(char *line, char *to_find);
bool			check_character(char c);
void			init_sprites(t_data *data);
void			free_and_exit(t_data *data, int i);
int				is_adjacent_to_dollar(t_data *data, int x, int y);
int				is_direction_character(t_data *data, int x, int y);
bool			draw_doors(t_data *data, double wall_hit_x,
					double wall_hit_y, t_ray ray);
#endif

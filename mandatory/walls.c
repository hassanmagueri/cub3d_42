/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:04:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/08/06 17:11:19 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

double ray_distance(double dx, double dy)
{
	return (sqrt(pow(dx, 2) + pow(dy, 2)));
}

char *swap_bytes(char *str)
{
	unsigned char tmp;

	tmp = str[0];
	str[0] = str[3];
	str[3] = tmp;
	tmp = str[2];
	str[2] = str[1];
	str[1] = tmp;
	return str;
}

void	ft_put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	swap_bytes((char *)(&color));
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
				mlx_put_pixel(img, x, y, color);
}


// int	wall_painting(t_data *data, t_ray ray , double ray_dist , double wall_height, mlx_image_t *img , int x)
// {
// 	t_map map=data->map;
// 	uint32_t *p_clrs = (uint32_t *)data->texture->pixels;
// 	int i;
	
// 	i = 0;
// 	double wall_top_pixel=((WINDOW_HEIGHT) / 2) - (wall_height / 2);
// 	if (wall_top_pixel < 0)
// 		wall_top_pixel = 0;
// 	int x_col = ray.is_vr ? 0: (int)(data->player.x + ray.dx * ray.direct) % data->texture->width;

// 	// p_clrs[x_col + img->width];
// 	double wall_bottom_pixel=((WINDOW_HEIGHT) /2) + (wall_height/ 2);
	
// 	if(wall_bottom_pixel > (WINDOW_HEIGHT))
// 		wall_bottom_pixel = WINDOW_HEIGHT ;
// 	int y = 0;
// 	while (wall_top_pixel <= wall_bottom_pixel && (y < data->texture->height))
// 	{
// 		int size_bytes = (wall_height / data->texture->height);
		
// 		i = 0;
			
// 		while (i < size_bytes)
// 		{
// 			ft_put_pixel(img, x, wall_top_pixel , p_clrs[x_col + (data->texture->width * y)]);
// 			i++;
// 		}
// 		if (i == 0)
// 		{
// 			ft_put_pixel(img, x, wall_top_pixel , p_clrs[x_col + (data->texture->width * y - )]);
// 			size_bytes++;
// 		}
// 		y++;
// 		wall_top_pixel += size_bytes;
// 	}
	
// 	return (1);
// }

// int wall_painting(t_data *data, t_ray ray, double wall_height, mlx_image_t *img, int x) {
// 	t_map map = data->map;
// 	uint32_t *p_clrs = (uint32_t *)data->texture->pixels;
// 	double wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_height / 2);
// 	if (wall_top_pixel < 0) wall_top_pixel = 0;

// 	double wall_hit_x = data->player.x + ray.dx ;
// 	double wall_hit_y = data->player.y + ray.dy ;
	
// 	int offX;
// 	if (ray.is_vr)
// 		offX = (int)wall_hit_y % data->texture->width;
// 	else
// 		offX = (int)wall_hit_x % data->texture->width;

// 	double wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_height / 2);
// 	if (wall_bottom_pixel > WINDOW_HEIGHT) wall_bottom_pixel = WINDOW_HEIGHT;

// 	int y =0;
// 	unsigned long index = 0;
// 	while(y < wall_top_pixel)
// 	{
// 		mlx_put_pixel(img, x, y, CYAN);
// 		y++;
// 	}
// 	// if (wall_height > WINDOW_HEIGHT)
// 	// 	y = wall_height / 2 - WINDOW_HEIGHT / 2;
// 	// printf("y: %f\n", wall_top_pixel);
// 		// printf("is begger\n");
// 	y = wall_top_pixel;
// 	while (wall_top_pixel < wall_bottom_pixel && index < data->texture->width * data->texture->height)
// 	{
// 		int current_y_pixel_wall = y + wall_height / 2 - WINDOW_HEIGHT / 2;
// 		int offY_txt = current_y_pixel_wall * data->texture->height / wall_height;
// 		index = (data->texture->width * offY_txt) + offX;
// 		if (index < data->texture->height * data->texture->width)
// 			ft_put_pixel(img, x, (int)y, p_clrs[index]);
// 		y++;
// 	}
// 	while(y < WINDOW_HEIGHT)
// 	{
// 		mlx_put_pixel(img, x, y, BLACK);
// 		y++;
// 	}
// 	return (1);
// }

int painting_part_col(mlx_image_t *img, int start, int end, int x, t_clr color)
{
	int y = start;
	while(y < end)
	{
		uint32_t c = ft_pixel(color);
		mlx_put_pixel(img, x, y, ft_pixel(color));
		y++;
	}
	return 0;
}

int wall_painting(t_data *data, t_ray ray, double wall_height, mlx_image_t *img, int x, mlx_texture_t *texture) {
	t_map map = data->map;
	uint32_t *p_clrs = (uint32_t *)texture->pixels;
		
	
	double wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	if (wall_top_pixel < 0) wall_top_pixel = 0;

	double wall_hit_x = data->player.x + ray.dx ;
	double wall_hit_y = data->player.y + ray.dy ;
	
	int offX;
	if (ray.is_vr)
		offX = (int)wall_hit_y % texture->width;
	else
		offX = (int)wall_hit_x % texture->width; // ??

	double wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_height / 2);
	if (wall_bottom_pixel > WINDOW_HEIGHT) wall_bottom_pixel = WINDOW_HEIGHT;

	int y =0;
	unsigned long index = 0;
	// painting_part_col(img, 0, wall_top_pixel,x, data->ceiling);
	y = wall_top_pixel;
	while (y <= wall_bottom_pixel && index < texture->width * texture->height)
	{
		// int dist_top_text = y - wall_top_pixel;
		int dist_top_text = y - WINDOW_HEIGHT / 2 + wall_height / 2;
		int offY = dist_top_text * texture->height / wall_height;
		index = (texture->width * offY) + offX;
		if (index < texture->height * texture->width)
			ft_put_pixel(img, x , y, p_clrs[index]);
		y++;
	}
	// painting_part_col(img, wall_bottom_pixel, WINDOW_HEIGHT, x, data->floor);
	return (1);
}

// void project_walls(t_data *data)
// {
	
// 	int i;
// 	t_ray *rays;
// 	double  ray_dist;
// 	double wall_expected_height;
// 	t_textures textures;
// 	static mlx_image_t *img;
	
// 	rays = data->rays;
// 	i = 0;
// 	// if (img)
// 	// 	mlx_delete_image(data->mlx, img);
// 	// reset_img(data->window_img);
// 	img = data->window_img;
// 	int distanceProjectionPlane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
// 	textures = data->textures;
// 	while (i < NUM_RAYS)
// 	{
// 		double correct_ray;

// 		ray_dist = ray_distance(rays[i].dx, rays[i].dy);
// 		correct_ray = ray_dist * cos(rays[i].angle - data->player.angle);
// 		wall_expected_height = (TILE_SIZE / correct_ray * distanceProjectionPlane);
// 		if (rays[i].direct == -1 && rays[i].is_vr)
// 			wall_painting(data,rays[i], wall_expected_height, img , i, textures.NO);
// 		else if (rays[i].direct == -1 && !rays[i].is_vr)
// 			wall_painting(data,rays[i], wall_expected_height, img , i, textures.SO);
// 		else if (rays[i].direct == 1 && rays[i].is_vr)
// 			wall_painting(data,rays[i], wall_expected_height, img , i, textures.WE);
// 		else if (rays[i].direct == 1 && !rays[i].is_vr)
// 			wall_painting(data,rays[i], wall_expected_height, img , i, textures.EA);
// 		i++;
// 	}
// }

// void project_walls(t_data *data)
void project_walls(t_data *data, t_ray ray, int x)
{
	
	double  ray_dist;
	double wall_expected_height;
	t_textures textures;
	static mlx_image_t *img;

	img = data->window_img;
	int distanceProjectionPlane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	textures = data->textures;
	double correct_ray;

	ray_dist = ray_distance(ray.dx, ray.dy);
	correct_ray = ray_dist * cos(ray.angle - data->player.angle);
	wall_expected_height = (TILE_SIZE / correct_ray * distanceProjectionPlane);
	if (ray.direct == -1 && ray.is_vr)
		wall_painting(data,ray, wall_expected_height, img , x, textures.NO);
	else if (ray.direct == -1 && !ray.is_vr)
		wall_painting(data,ray, wall_expected_height, img , x, textures.SO);
	else if (ray.direct == 1 && ray.is_vr)
		wall_painting(data,ray, wall_expected_height, img , x, textures.WE);
	else if (ray.direct == 1 && !ray.is_vr)
		wall_painting(data,ray, wall_expected_height, img , x, textures.EA);
}

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../MLX/MLX42.h"
#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

char *swap(char *str)
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

int32_t	main(void)
{
	// Start mlx
	mlx_t* mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Test", true);
	if (!mlx)
        error();

	// Try to load the file
	// mlx_texture_t* texture = mlx_load_png("./-png.png");
	mlx_texture_t* texture = mlx_load_png("../images/solid_blue.png");
	if (!texture)
        error();
	
	printf("%x\n", texture->pixels[0]);
	printf("%x\n", texture->pixels[1]);
	printf("%x\n", texture->pixels[2]);
	printf("%x\n", texture->pixels[3]);
	uint32_t *p =(uint32_t *)texture->pixels;
	

	// printf("%x", texture->pixels[0]); //r
	// printf("%x", texture->pixels[1]); // g
	// printf("%x", texture->pixels[2]);// b
	// printf("%x\n", texture->pixels[3]);// a

	printf("%x\n", p[0]);
	swap((char *)p);
	
	printf("%x\n", p[0]);

	// Convert texture to a displayable image
	mlx_image_t* img = mlx_texture_to_image(mlx, texture);
	if (!img)
        error();

	// Display the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();
	

	mlx_loop(mlx);

	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

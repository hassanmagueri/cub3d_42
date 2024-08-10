# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 20:04:47 by emagueri          #+#    #+#              #
#    Updated: 2024/08/10 15:13:56 by belguabd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc  -Ofast   -g#-Wall -Wextra -Werror -Ofast  -fsanitize=address -g 
PARSING=parsing
UTILS=utils
GET_NEXT_LINE=$(UTILS)/get_next_line

NAME = cub3D
MLX_NAME = MLX/libmlx42.a
MLX_FLAGS = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
SRC = main.c draw_objects.c player.c mlx_help.c ray.c walls.c minimap.c\
	$(GET_NEXT_LINE)/get_next_line.c \
	$(GET_NEXT_LINE)/get_next_line_utils.c \
	$(UTILS)/ft_strcmp.c $(UTILS)/ft_strlcat.c $(UTILS)/ft_putendl_fd.c $(UTILS)/ft_split.c \
	$(UTILS)/ft_substr.c $(UTILS)/ft_strtrim.c $(UTILS)/ft_isdigit.c $(UTILS)/ft_atoi.c \
	$(UTILS)/ft_itoa.c \
	$(PARSING)/parsing.c 

OBJ = $(SRC:.c=.o)


all: $(NAME) # !!!

$(NAME): $(OBJ) cub3d.h
	$(CC) $(MLX_FLAGS) $(MLX_NAME) $(OBJ) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) -c $< -o $@  

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
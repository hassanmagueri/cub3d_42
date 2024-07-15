# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 14:56:23 by belguabd          #+#    #+#              #
#    Updated: 2024/07/15 01:28:32 by belguabd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc -g -fsanitize=address #-Wall -Wextra -Werror

READ_NEXT_LINE=read_next_line
UTILS=utils

NAME = cub3d
MLX_NAME = libmlx42.a
MLX_FLAGS = -Iinclude -lglfw -L"/Users/emagueri/.brew/opt/glfw/lib/"
SRC = main.c \
	$(READ_NEXT_LINE)/get_next_line.c \
	$(READ_NEXT_LINE)/get_next_line_utils.c \
	$(UTILS)/ft_strcmp.c $(UTILS)/ft_strlcat.c $(UTILS)/ft_putendl_fd.c $(UTILS)/ft_split.c \
	$(UTILS)/ft_substr.c $(UTILS)/ft_strtrim.c $(UTILS)/ft_isdigit.c $(UTILS)/ft_atoi.c
	

OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ) parse.h 
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c parse.h read_next_line/get_next_line.h
	$(CC) -c $< -o $@ 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
CC = cc    -g -fsanitize=address#-Wall -Wextra -Werror
#==============folders==============#
PARSING=parsing
UTILS=utils
MEM_MGR=mem_mgr
GET_NEXT_LINE=$(UTILS)/get_next_line
MANDATORY=mandatory
BONUS=bonus


NAME = cub3D
NAME_BONUS=bonus
MLX_NAME = MLX/libmlx42.a
MLX_FLAGS = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
SRC = $(MANDATORY)/main.c $(MANDATORY)/draw_objects.c $(MANDATORY)/player.c \
	$(MANDATORY)/mlx_help.c $(MANDATORY)/ray.c $(MANDATORY)/walls.c \
	$(MANDATORY)/$(GET_NEXT_LINE)/get_next_line.c \
	$(MANDATORY)/$(GET_NEXT_LINE)/get_next_line_utils.c \
	$(MANDATORY)/$(UTILS)/ft_strcmp.c $(MANDATORY)/$(UTILS)/ft_strlcat.c \
	$(MANDATORY)/$(UTILS)/ft_putendl_fd.c $(MANDATORY)/$(UTILS)/ft_split.c \
	$(MANDATORY)/$(UTILS)/ft_substr.c $(MANDATORY)/$(UTILS)/ft_strtrim.c \
	$(MANDATORY)/$(UTILS)/ft_isdigit.c $(MANDATORY)/$(UTILS)/ft_atoi.c \
	$(MANDATORY)/$(PARSING)/load_map_data.c $(MANDATORY)/$(PARSING)/load_map_data_utils.c \
	$(MANDATORY)/$(PARSING)/init_clrs_dirs.c $(MANDATORY)/$(PARSING)/parse_map.c \
	$(MANDATORY)/$(PARSING)/utils.c $(MANDATORY)/$(PARSING)/validate_dirs_clrs.c \
	$(MANDATORY)/$(PARSING)/validate_dirs_clrs_utils.c $(MANDATORY)/$(PARSING)/validate_top_map.c \
#$(MANDATORY)/$(MEM_MGR)/mem_mgr.c

SRC_BONUS=$(BONUS)/main_bonus.c $(BONUS)/draw_objects_bonus.c $(BONUS)/player_bonus.c \
	$(BONUS)/mlx_help_bonus.c $(BONUS)/ray_bonus.c $(BONUS)/walls_bonus.c $(BONUS)/minimap_bonus.c \
	$(BONUS)/$(PARSING)/load_map_data.c $(BONUS)/$(PARSING)/load_map_data_utils.c \
	$(BONUS)/$(PARSING)/init_clrs_dirs.c $(BONUS)/$(PARSING)/parse_map.c \
	$(BONUS)/$(PARSING)/utils.c $(BONUS)/$(PARSING)/validate_dirs_clrs.c \
	$(BONUS)/$(PARSING)/validate_dirs_clrs_utils.c $(BONUS)/$(PARSING)/validate_top_map.c \



OBJ = $(SRC:.c=.o)


all: $(NAME) 

$(NAME): $(OBJ) 
	$(CC) $(MLX_FLAGS) $(MANDATORY)/$(MLX_NAME) $(OBJ) -o $(NAME)

$(MANDATORY)/%.o:$(MANDATORY)/%.c $(MANDATORY)/cub3d.h
	$(CC) -c $< -o $@  

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
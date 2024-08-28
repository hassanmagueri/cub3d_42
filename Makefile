CC = cc -Ofast 
CC += -Wall -Wextra -Werror 
# CC += -g -fsanitize=address

#==============folders==============#
PARSING=parsing
UTILS=utils
MEM_MGR=mem_mgr
GET_NEXT_LINE=$(UTILS)/get_next_line
MANDATORY=mandatory
BONUS=bonus


NAME = cub3D
NAME_BONUS=cub3D_bonus
MLX_NAME = MLX/libmlx42.a
MLX_FLAGS = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
# $(MANDATORY)/ray.c 
SRC = $(MANDATORY)/main.c $(MANDATORY)/draw_objects.c $(MANDATORY)/player.c  \
	$(MANDATORY)/mlx_help.c \
	$(MANDATORY)/utils.c \
	$(MANDATORY)/protected_mlx.c $(MANDATORY)/protected_mlx_utils.c \
	$(MANDATORY)/rays.c $(MANDATORY)/rays_utils.c \
	$(MANDATORY)/walls.c $(MANDATORY)/wall_utils.c\
	$(MANDATORY)/$(GET_NEXT_LINE)/get_next_line.c \
	$(MANDATORY)/$(GET_NEXT_LINE)/get_next_line_utils.c \
	$(MANDATORY)/$(UTILS)/ft_strcmp.c $(MANDATORY)/$(UTILS)/ft_strncmp.c \
	$(MANDATORY)/$(UTILS)/ft_strlcat.c \
	$(MANDATORY)/$(UTILS)/ft_putendl_fd.c $(MANDATORY)/$(UTILS)/ft_split.c \
	$(MANDATORY)/$(UTILS)/ft_substr.c $(MANDATORY)/$(UTILS)/ft_strtrim.c \
	$(MANDATORY)/$(UTILS)/ft_isdigit.c $(MANDATORY)/$(UTILS)/ft_atoi.c \
	$(MANDATORY)/$(PARSING)/load_map_data.c $(MANDATORY)/$(PARSING)/load_map_data_utils.c \
	$(MANDATORY)/$(PARSING)/init_clrs_dirs.c $(MANDATORY)/$(PARSING)/parse_map.c \
	$(MANDATORY)/$(PARSING)/utils.c $(MANDATORY)/$(PARSING)/validate_dirs_clrs.c \
	$(MANDATORY)/$(PARSING)/validate_top_map_utils.c\
	$(MANDATORY)/mem_mgr/mem_mgr.c \
	$(MANDATORY)/$(PARSING)/validate_dirs_clrs_utils.c $(MANDATORY)/$(PARSING)/validate_top_map.c \

OBJ = $(SRC:.c=.o)


SRC_BONUS=$(BONUS)/main_bonus.c $(BONUS)/draw_objects_bonus.c $(BONUS)/player_bonus.c\
	$(BONUS)/protected_mlx_bonus.c $(BONUS)/protected_mlx_utils_bonus.c \
	$(BONUS)/utils_bonus.c $(BONUS)/utils1_bonus.c \
	$(BONUS)/$(GET_NEXT_LINE)/get_next_line_bonus.c \
	$(BONUS)/$(GET_NEXT_LINE)/get_next_line_utils_bonus.c \
	$(BONUS)/$(UTILS)/ft_strcmp_bonus.c $(BONUS)/$(UTILS)/ft_strlcat_bonus.c \
	$(BONUS)/$(UTILS)/ft_putendl_fd_bonus.c $(BONUS)/$(UTILS)/ft_split_bonus.c \
	$(BONUS)/$(UTILS)/ft_substr_bonus.c $(BONUS)/$(UTILS)/ft_strtrim_bonus.c \
	$(BONUS)/$(UTILS)/ft_isdigit_bonus.c $(BONUS)/$(UTILS)/ft_atoi_bonus.c $(BONUS)/$(UTILS)/ft_itoa_bonus.c \
	$(BONUS)/mlx_help_bonus.c $(BONUS)/rays_bonus.c $(BONUS)/rays_utils_bonus.c $(BONUS)/walls_bonus.c \
	$(BONUS)/minimap_bonus.c $(BONUS)/minimap_utils_bonus.c \
	$(BONUS)/$(PARSING)/load_map_data_bonus.c $(BONUS)/$(PARSING)/load_map_data_utils_bonus.c \
	$(BONUS)/$(PARSING)/init_clrs_dirs_bonus.c $(BONUS)/$(PARSING)/parse_map_bonus.c \
	$(BONUS)/$(PARSING)/utils_bonus.c $(BONUS)/$(PARSING)/validate_dirs_clrs_bonus.c \
	$(BONUS)/doors_bonus.c $(BONUS)/doors_utils_bonus.c \
	$(BONUS)/mem_mgr/mem_mgr_bonus.c $(BONUS)/cleanup_mlx/cleanup_imges_textures.c\
	$(BONUS)/sprite_bonus.c $(BONUS)/mouse_bonus.c $(BONUS)/walls_utils_bonus.c\
	$(BONUS)/$(PARSING)/validate_dirs_clrs_utils1_bonus.c $(BONUS)/$(PARSING)/validate_top_map_bonus.c \
	$(BONUS)/$(PARSING)/validate_dirs_clrs_utils2_bonus.c

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME) 


$(NAME): $(OBJ) 
	$(CC) $(MLX_FLAGS) $(MANDATORY)/$(MLX_NAME) $(OBJ) -o $(NAME)

$(MANDATORY)/%.o:$(MANDATORY)/%.c $(MANDATORY)/cub3d.h
	$(CC) -c $< -o $@  

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(MLX_FLAGS) $(BONUS)/$(MLX_NAME) $(OBJ_BONUS) -o $(NAME_BONUS)

$(BONUS)/%.o:$(BONUS)/%.c $(BONUS)/cub3d_bonus.h
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all 
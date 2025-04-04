# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source and object files
SRC_DIR = src
SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/draw_line.c \
	  $(SRC_DIR)/initiate_struct_values.c \
	  $(SRC_DIR)/player_functions.c \
	  $(SRC_DIR)/map_walls_functions.c \
	  $(SRC_DIR)/draw_rays.c \
	  $(SRC_DIR)/ray_wall_hit.c \
	  $(SRC_DIR)/set_values_each_ray.c \
	  $(SRC_DIR)/find_intercepts_steps.c \
	  $(SRC_DIR)/check_ray_between_limits.c \
	  $(SRC_DIR)/free.c \
	  $(SRC_DIR)/parsing_map.c \
	  $(SRC_DIR)/parsing_elements.c \
	  $(SRC_DIR)/validate_map.c \
	  $(SRC_DIR)/utils.c \
	  $(SRC_DIR)/set_dir_player_pos.c

OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
INCLUDE = -I.

# Program name
NAME = cub3D

# Libft integration
LIBFT_DIR = libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -c $< -o $@

# Link object files with libraries for macbook manuel
# $(NAME): $(OBJ) MLX42/build/libmlx42.a
# 	@make all -C ./libft
# 	$(CC) $(CFLAGS) $^ $(INCLUDE) -Llibft -lft -LMLX42/build -lmlx42 -L/opt/homebrew/lib -lglfw -lm -o $(NAME)

# # Link object files with libraries
$(NAME): $(OBJ) MLX42/build/libmlx42.a
	@make all -C ./libft
	$(CC) $(CFLAGS) $^ $(INCLUDE) -Llibft -lft -LMLX42/build -lmlx42 -lglfw -lm -o $(NAME)

MLX42/build/libmlx42.a:
	cd MLX42 && cmake -B build && make -C build -j4

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	@make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re

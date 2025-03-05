# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source and object files
SRC_DIR = src
SRC = $(SRC_DIR)/main.c 
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Program name
NAME = cub3D

# Libft integration
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LDFLAGS = -L$(LIBFT_DIR) -lft

#mlx integration
MLX_FLAGS = -LMLX42/build -lmlx42 -lglfw -lm

MLX42/build/libmlx42.a:
	cd MLX42 && cmake -B build && make -C build -j4

# Rules
all: $(NAME)

# Compile libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Link object files with libraries
$(NAME): $(OBJ) $(LIBFT) MLX42/build/libmlx42.a
	$(CC) $(OBJ) $(LDFLAGS) $(MLX_FLAGS) -o $(NAME)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	# $(MAKE) -C $(MLX_DIR) clean # Uncomment if needed

# Full clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
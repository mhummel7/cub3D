# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source and object files
SRC_DIR = src
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/parsing.c
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Program name
NAME = cub3D

# Libft integration
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LDFLAGS = -L$(LIBFT_DIR) -lft

# MiniLibX integration for macOS
MLX_DIR = minilibx_opengl
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm

# Rules
all: $(NAME)

# Compile libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compile miniLibX
$(MLX):
	$(MAKE) -C $(MLX_DIR)

# Link object files with libraries
$(NAME): $(OBJ) $(LIBFT) $(MLX)
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
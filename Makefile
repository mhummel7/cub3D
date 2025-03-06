# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source and object files
SRC_DIR = src
SRC = $(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing_elements.c \
		$(SRC_DIR)/parsing_map.c \
		$(SRC_DIR)/validate_map.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/free.c \
		$(SRC_DIR)/mlx_utils.c
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Program name
NAME = cub3D

# Libft integration
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LDFLAGS = -L$(LIBFT_DIR) -lft

# MLX42 integration
MLX42_DIR = MLX42
MLX42_FLAGS = -L$(MLX42_DIR)/build -lmlx42 -lglfw -lm

# Rules
all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) $(MLX42_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(MLX42_DIR)/include/MLX42 -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
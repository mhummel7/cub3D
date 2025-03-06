# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source and object files
SRC_DIR = src
SRC = $(SRC_DIR)/main.c 
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
INCLUDE		=	-I.

# Program name
NAME = cub3D

# Libft integration
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LDFLAGS = -L$(LIBFT_DIR) -lft

MLX42/build/libmlx42.a:
	cd MLX42 && cmake -B build && make -C build -j4

# Rules
all: $(NAME)

# Link object files with libraries
$(NAME): $(OBJ) MLX42/build/libmlx42.a
	@make all -C ./libft
	$(CC) $^ ${INCLUDE}  -Llibft -lft -LMLX42/build -lmlx42 -lglfw -lm -o $(NAME)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	@make clean -C ./libft

# Full clean
fclean: clean
	rm -f $(NAME)
	@make fclean -C ./libft

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
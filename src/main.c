/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:57:50 by mhummel           #+#    #+#             */
/*   Updated: 2025/03/05 14:25:07 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_exit(const char *message)
{
	write(2, "Error: ", 7);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	game->dynamic_layer = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->static_layer = mlx_new_image(game->mlx, WIDTH, HEIGHT);
}

// Initializes game struct with default (safe) values / -1 means uninitialized
void	init_game(t_game *game)
{
	game->no_texture = NULL;
	game->so_texture = NULL;
	game->we_texture = NULL;
	game->ea_texture = NULL;
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->map = NULL;
	game->map_height = 0;
	game->map_width = 0;
	game->pos_x = -1;
	game->pos_y = -1;
	game->dir_x = 0;
	game->dir_y = 0;
	game->mlx = NULL;
	game->dynamic_layer = NULL;
	game->static_layer = NULL;
}

// Checks if moving to (new_x, new_y) hits a wall or goes out of bounds
// int	check_collision(t_game *game, double new_x, double new_y)
// {
// 	int	map_x;
// 	int	map_y;

// 	map_x = (int)new_x;
// 	map_y = (int)new_y;
// 	if (map_x < 0 || map_x >= game->map_width) //checks if out of bounds
// 		return (1);
// 	if (map_y < 0 || map_y >= game->map_height)
// 		return (1);
// 	if (game->map[map_y][map_x] == '1') // checking if there is a wall
// 		return (1);
// 	return (0); // if there is no collision
// }

// Handles key presses, ESC key closes the window and WASD for movement
// static void	key_hook(mlx_key_data_t keydata, void *param)
// {
// 	t_game	*game;
// 	double	move_speed;
// 	double	rot_speed;

// 	game = (t_game *)param;
// 	move_speed = 0.1; // movement speed(can change that if its to fast or to slow we will see)
// 	rot_speed = 0.05; // rotation speed, can also be changed
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
// 		mlx_close_window(game->mlx);
// 	handle_movement(game, keydata, move_speed);
// 	handle_strafe(game, keydata, move_speed);
// 	handle_rotation(game, keydata, rot_speed);
// 	printf("Pos: (%.2f, %.2f), Dir: (%.2f, %.2f)\n", game->pos_x, game->pos_y,
// 		game->dir_x, game->dir_y); // shows the position and direction of the player in the console
// }

void render(void* param)
{
    t_game* game = (t_game*)param;

    // Clear the image with a color (e.g., black)
    memset(game->dynamic_layer->pixels, 0, game->dynamic_layer->width * game->dynamic_layer->height * sizeof(int32_t));

    // Draw the cube (a rectangle) at its current position
    for (int y = 0; y < MOVING_OBJECT_SIZE; y++) {
        for (int x = 0; x < MOVING_OBJECT_SIZE; x++) {
            mlx_put_pixel(game->dynamic_layer, game->pos_x + x, game->pos_y + y, 0xFF0000FF); // Red color
        }
    }

    // Render the image to the window
    mlx_image_to_window(game->mlx, game->dynamic_layer, 0, 0);
}

void add_static_pixels(t_game *game, char* filename)
{
	int base_x = 30;
	int base_y = 30;
	(void)game;
	int fd = open(filename, O_RDONLY);
	char *str = get_next_line(fd);
	int add_y = 1;
	int base_x_mult = base_x;
	int base_y_mult = 30;
	while(str)
	{
		int x = 0;
		while(str[x] != '\n' && str[x] != '\0')
		{
			if (str[x] == '1')
				for (int y = 0; y < CUBE_SIZE; y++)
				{
					for (int x = 0; x < CUBE_SIZE; x++)
					{
						mlx_put_pixel(game->static_layer, base_x_mult + x, base_y_mult + y, 0xFFFFFFFF); // White color
					}
				}
			else if(str[x] == 'N' || str[x] == 'S' || str[x] == 'E' || str[x] == 'W')
			{
				game->pos_x = base_x_mult;
				game->pos_y = base_y_mult;
			}
			base_x_mult += 30;
			x++;
		}
		add_y++;
		base_x_mult = 30;
		base_y_mult = base_y * add_y;
		str = get_next_line(fd);
	}

	mlx_image_to_window(game->mlx, game->static_layer, 0, 0);
}

bool is_wall(mlx_image_t *image, int x, int y) {
    if (x < 0 || y < 0 || x >= (int)image->width || y >= (int)image->height) {
        return true; // Out of bounds is treated as a wall
    }
    uint32_t color = ((uint32_t *)image->pixels)[y * image->width + x];
    return (color == 0xFFFFFFFF); // Check if the pixel is white
}

bool check_collision(t_game *game, int new_x, int new_y) {
    for (int y = 0; y < MOVING_OBJECT_SIZE; y++) {
        for (int x = 0; x < MOVING_OBJECT_SIZE; x++) {
            if (is_wall(game->static_layer, new_x + x, new_y + y)) {
                return true; // Collision detected
            }
        }
    }
    return false; // No collision
}

void keys_hook(mlx_key_data_t keydata, void* param)
{
    t_game *game = (t_game *)param;
    int new_x = game->pos_x;
    int new_y = game->pos_y;

    // Calculate new position based on key input
    if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_y -= 10; // Move up
    else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_y += 10; // Move down
    else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_x -= 10; // Move left
    else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        new_x += 10; // Move right

    // Check for collision before updating position
    if (!check_collision(game, new_x, new_y))
	{
        game->pos_x = new_x;
        game->pos_y = new_y;
    }
}

// Main entry point: sets up game, parses file, starts MLX42
// a lot of debug messages to test it because i was having problems getting it started
int	main(int argc, char **argv)
{
	t_game game;
	if (argc != 2 || !ft_strrchr(argv[1], '.') || ft_strcmp(ft_strrchr(argv[1], '.'), ".cub"))
		error_exit("Usage: ./cub3D <map.cub>"); // checks if the file is a .cub file and the number of arguments
	init_game(&game); // initializes game struct
	printf("Parsing file...\n");
	// parse_cub_file(argv[1], &game); // parses the cub file
	printf("Initializing MLX42...\n");
	init_mlx(&game); // initializes MLX42
	add_static_pixels(&game, argv[1]);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_key_hook(game.mlx, keys_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	// printf("Drawing pixel...\n");
	// mlx_put_pixel(game.dynamic_layer, 400, 300, 0xFF0000FF); // draws a red pixel dot in the middle
	// printf("Displaying image...\n");
	//mlx_image_to_window(game.mlx, game.dynamic_layer, 0, 0); // displays image
	//printf("Setting key hook...\n");
	//mlx_key_hook(game.mlx, key_hook, &game); // sets up key handling
	//printf("Entering MLX loop...\n");
	//mlx_loop(game.mlx); // starts MLX42 event loop
	//printf("Terminating MLX42...\n");
	//mlx_terminate(game.mlx); // cleans up mlx42 resources
	//printf("Freeing game...\n");
	//free_game(&game); // free game struct memory
	//printf("Done.\n");
	return (0);
}

// should be finished im looking more into it tomorrow
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:57:50 by mhummel           #+#    #+#             */
/*   Updated: 2025/03/13 14:03:37 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	render(void *param)
{
	t_game	*game;
	int		radius;
	int		center_x;
	int		center_y;
	int		x;
	int		y;

	game = (t_game *)param;
	// Clear the image with a color (e.g., black)
	memset(game->dynamic_layer->pixels, 0, game->dynamic_layer->width
		* game->dynamic_layer->height * sizeof(int32_t));
	// Define the radius of the circle
	radius = MOVING_OBJECT_SIZE / 2;
	// Calculate the center of the circle
	center_x = game->pos_x + radius;
	center_y = game->pos_y + radius;
	// Midpoint circle algorithm (filled circle)
	x = radius;
	y = 0;
	int p = 1 - radius; // Decision parameter
	while (x >= y)
	{
		// Draw horizontal lines to fill the circle
		for (int i = -x; i <= x; i++)
		{
			mlx_put_pixel(game->dynamic_layer, center_x + i, center_y + y,
				0xFF0000FF); // Red color
			mlx_put_pixel(game->dynamic_layer, center_x + i, center_y - y,
				0xFF0000FF);
		}
		for (int i = -y; i <= y; i++)
		{
			mlx_put_pixel(game->dynamic_layer, center_x + i, center_y + x,
				0xFF0000FF);
			mlx_put_pixel(game->dynamic_layer, center_x + i, center_y - x,
				0xFF0000FF);
		}
		y++;
		// Update the decision parameter
		if (p <= 0)
		{
			p = p + 2 * y + 1;
		}
		else
		{
			x--;
			p = p + 2 * y - 2 * x + 1;
		}
	}
	// Render the image to the window
	mlx_image_to_window(game->mlx, game->dynamic_layer, 0, 0);
}

void	add_static_pixels(t_game *game, char *filename)
{
	int		base_x;
	int		base_y;
	int		fd;
	char	*str;
	int		add_y;
	int		base_x_mult;
	int		base_y_mult;
	int		x;

	base_x = 30;
	base_y = 30;
	(void)game;
	fd = open(filename, O_RDONLY);
	str = get_next_line(fd);
	add_y = 1;
	base_x_mult = base_x;
	base_y_mult = 30;
	while (str)
	{
		x = 0;
		while (str[x] != '\n' && str[x] != '\0')
		{
			if (str[x] == '1')
				for (int y = 0; y < CUBE_SIZE; y++)
				{
					for (int x = 0; x < CUBE_SIZE; x++)
					{
						mlx_put_pixel(game->static_layer, base_x_mult + x,
							base_y_mult + y, 0xFFFFFFFF); // White color
					}
				}
			else if (str[x] == 'N' || str[x] == 'S' || str[x] == 'E'
				|| str[x] == 'W')
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
		free(str);
		str = get_next_line(fd);
	}
	mlx_image_to_window(game->mlx, game->static_layer, 0, 0);
}

bool	is_wall(mlx_image_t *image, int x, int y)
{
	uint32_t	color;

	if (x < 0 || y < 0 || x >= (int)image->width || y >= (int)image->height)
	{
		return (true); // Out of bounds is treated as a wall
	}
	color = ((uint32_t *)image->pixels)[y * image->width + x];
	return (color == 0xFFFFFFFF); // Check if the pixel is white
}

bool	check_collision(t_game *game, int new_x, int new_y)
{
	for (int y = 0; y < MOVING_OBJECT_SIZE; y++)
	{
		for (int x = 0; x < MOVING_OBJECT_SIZE; x++)
		{
			if (is_wall(game->static_layer, new_x + x, new_y + y))
			{
				return (true); // Collision detected
			}
		}
	}
	return (false); // No collision
}

// Handles key presses, ESC key closes the window and WASD for movement
void	keys_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		new_x;
	int		new_y;

	game = (t_game *)param;
	new_x = game->pos_x;
	new_y = game->pos_y;
	// Calculate new position based on key input
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		new_y -= 5; // Move up
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		new_y += 5; // Move down
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		new_x -= 5; // Move left
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		new_x += 5; // Move right
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
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
	t_game	game;

	if (argc != 2 || !ft_strrchr(argv[1], '.') || ft_strcmp(ft_strrchr(argv[1],
				'.'), ".cub"))
		error_exit("Usage: ./cub3D <map.cub>");
			// checks if the file is a .cub file and the number of arguments
	init_game(&game);                           // initializes game struct
	printf("Parsing file...\n");
	parse_cub_file(argv[1], &game); // parses the cub file
	printf("Initializing MLX42...\n");
	init_mlx(&game); // initializes MLX42
	printf("Drawing pixel...\n");
	add_static_pixels(&game, argv[1]);
	printf("Displaying image...\n");
	printf("Setting key hook...\n");
	mlx_key_hook(game.mlx, keys_hook, &game);
	printf("Entering MLX loop...\n");
	mlx_loop_hook(game.mlx, render, &game); // sets up loop hook for walking etc
	printf("Entering loop hook...\n");
	mlx_loop(game.mlx); // starts MLX42 event loop
	printf("Terminating MLX42...\n");
	mlx_terminate(game.mlx); // cleans up mlx42 resources
	printf("Freeing game...\n");
	free_game(&game); // free game struct memory
	printf("Done.\n");

	system("leaks cub3D"); // Check for memory leaks

	return (0);
}

// should be finished im looking more into it tomorrow
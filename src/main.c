/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:39:36 by frocha            #+#    #+#             */
/*   Updated: 2025/04/02 17:04:58 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_mlx(t_game *game)
{
	game->window_width = game->map_width * CUBE_SIZE;
    game->window_height = game->map_height * CUBE_SIZE;
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
	game->view_layer = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->dynamic_layer = mlx_new_image(game->mlx, game->window_width, game->window_height);
    game->static_layer = mlx_new_image(game->mlx, game->window_width, game->window_height);
	game->color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * SCREEN_WIDTH
			* SCREEN_HEIGHT);
	if (!game->mlx) printf("Error: mlx_init failed\n");
	if (!game->view_layer) printf("Error: view_layer creation failed\n");
	if (!game->dynamic_layer) printf("Error: dynamic_layer creation failed\n");
	if (!game->static_layer) printf("Error: static_layer creation failed\n");
	if (!game->color_buffer) printf("Error: color_buffer allocation failed\n");
}

void	keys_hook(mlx_key_data_t keydata, void *param)
{
	t_player	*player;

	player = (t_player *)param;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
		player->walk_direction = +1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		player->walk_direction = -1;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		player->turn_direction = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		player->turn_direction = +1;
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(player->game->mlx);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		player->walk_direction = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		player->walk_direction = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		player->turn_direction = 0;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		player->turn_direction = 0;
}

void	clear_color_buffer(t_game *game, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < SCREEN_WIDTH)
	{
		while (y < SCREEN_HEIGHT)
		{
			game->color_buffer[(SCREEN_WIDTH * y) + x] = color;
			y++;
		}
		x++;
	}
}

void	render(void *param)
{
	t_str_access	*str_access;
	t_game			*game;
	t_player		*player;
	t_rays			rays;

	str_access = (t_str_access *)param;
	str_access = (t_str_access *)param;
	game = str_access->game;
	player = str_access->player;
	ft_memset(game->dynamic_layer->pixels, 0, game->dynamic_layer->width
		* game->dynamic_layer->height * sizeof(int32_t));
	clear_color_buffer(game, 0xFF00FF00);
	// ft_memcpy(game->view_layer->pixels, game->color_buffer, SCREEN_HEIGHT
	//	* SCREEN_WIDTH * sizeof(uint32_t));
	ft_memset(game->view_layer->pixels, 220, SCREEN_HEIGHT * SCREEN_WIDTH
		* sizeof(int32_t));
	move_player(player);
	cast_all_rays(player, &rays);
	render_rays(player, &rays);
}

int check_argc(int argc, char **argv)
{
	if (argc != 2 || !ft_strrchr(argv[1], '.') || ft_strcmp(ft_strrchr(argv[1], '.'), ".cub"))
	{
		write(2, "Error: Usage: ./cub3D <map.cub>\n", 32);
		return (1);
	}
	return (0);
}

// Initializes game struct with default (safe) values / -1 means uninitialized
void init_game(t_game *game)
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
    game->view_layer = NULL;
    game->color_buffer = NULL;
    game->window_width = 0;  // Neu
    game->window_height = 0; // Neu
}

int main(int argc, char **argv)
{
    t_str_access stru_access;
    t_game *game;

    if (check_argc(argc, argv))
        return (1);

    initiate_str_access_values(&stru_access);
    game = stru_access.game;
    init_game(game); // Initialisiert t_game
	game->window_width = game->map_width * CUBE_SIZE;
    game->window_height = game->map_height * CUBE_SIZE;
    printf("Set window size: width = %d, height = %d\n", game->window_width, game->window_height);
    initiate_map(stru_access.map, argv[1], game);
    initiate_player(stru_access.player, game);
    stru_access.player->map = stru_access.map;
    init_mlx(game);
    mlx_image_to_window(game->mlx, game->view_layer, 0, 0);
    mlx_image_to_window(game->mlx, game->static_layer, 0, 0);
    mlx_image_to_window(game->mlx, game->dynamic_layer, 0, 0);
    add_static_pixels(&stru_access);
    mlx_loop_hook(game->mlx, render, &stru_access);
    mlx_key_hook(game->mlx, keys_hook, stru_access.player);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
    free_game(game);
    return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_str_access	stru_access;
// 	t_game			*game;

// 	if (check_argc(argc, argv))
// 		return (1);

// 	stru_access.map = NULL;
// 	stru_access.game = NULL;
// 	stru_access.player = NULL;
// 	initiate_str_access_values(&stru_access);
// 	game = stru_access.game;
// 	init_game(game); // Initialisiert t_game
// 	initiate_map(stru_access.map, argv[1], game);
// 	initiate_player(stru_access.player, game);
// 	stru_access.player->map = stru_access.map;
// 	init_mlx(game);
// 	mlx_image_to_window(game->mlx, game->view_layer, 0, 0);
// 	mlx_image_to_window(game->mlx, game->static_layer, 0, 0);
// 	mlx_image_to_window(game->mlx, game->dynamic_layer, 0, 0);
// 	add_static_pixels(&stru_access);
// 	mlx_loop_hook(game->mlx, render, &stru_access);
// 	mlx_key_hook(game->mlx, keys_hook, stru_access.player);
// 	mlx_loop(game->mlx);
// 	mlx_terminate(game->mlx);
// 	free_game(game);
// 	return (0);
// }

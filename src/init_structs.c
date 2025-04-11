/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:49:06 by frocha            #+#    #+#             */
/*   Updated: 2025/04/11 11:10:44 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_img_to_window(t_game *game)
{
	mlx_image_to_window(game->mlx, game->background_layer, 0, 0);
	mlx_image_to_window(game->mlx, game->wall_layer, 0, 0);
	mlx_image_to_window(game->mlx, game->static_layer, 0, 0);
	mlx_image_to_window(game->mlx, game->dynamic_layer, 0, 0);
}

void	init_mlx(t_game *game)
{
	game->window_width = game->map_width * CUBE_SIZE;
	game->window_height = game->map_height * CUBE_SIZE;
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
	game->background_layer = mlx_new_image(game->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	game->wall_layer = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->dynamic_layer = mlx_new_image(game->mlx, game->window_width,
			game->window_height);
	game->static_layer = mlx_new_image(game->mlx, game->window_width,
			game->window_height);
	if (!game->mlx)
		printf("Error: mlx_init failed\n");
	if (!game->background_layer)
		printf("Error: background_layer creation failed\n");
	if (!game->wall_layer)
		printf("Error: wall_layer creation failed\n");
	if (!game->dynamic_layer)
		printf("Error: dynamic_layer creation failed\n");
	if (!game->static_layer)
		printf("Error: static_layer creation failed\n");
}

void	init_game(t_game *game)
{
	game->filename = NULL;
	game->no_texture = NULL;
	game->so_texture = NULL;
	game->we_texture = NULL;
	game->ea_texture = NULL;
	game->no_tex = NULL;
	game->so_tex = NULL;
	game->we_tex = NULL;
	game->ea_tex = NULL;
	game->floor_color = 0xFFFFFFFF;
	game->ceiling_color = 0xFFFFFFFF;
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
	game->background_layer = NULL;
	game->window_width = 0;
	game->window_height = 0;
}

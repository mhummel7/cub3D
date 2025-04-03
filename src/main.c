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
	game->background_layer = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->wall_layer = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->dynamic_layer = mlx_new_image(game->mlx, game->window_width, game->window_height);
    game->static_layer = mlx_new_image(game->mlx, game->window_width, game->window_height);
	if (!game->mlx) printf("Error: mlx_init failed\n");
	if (!game->background_layer) printf("Error: background_layer creation failed\n");
	if (!game->wall_layer) printf("Error: wall_layer creation failed\n");
	if (!game->dynamic_layer) printf("Error: dynamic_layer creation failed\n");
	if (!game->static_layer) printf("Error: static_layer creation failed\n");
}

void	keys_hook(mlx_key_data_t keydata, void *param)
{
	t_player	*player;

	player = (t_player *)param;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
		player->walk_direction = +1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		player->walk_direction = -1;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS))
		player->turn_direction = -1;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS))
		player->turn_direction = +1;
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(player->game->mlx);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		player->walk_direction = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		player->walk_direction = 0;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
		player->turn_direction = 0;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
		player->turn_direction = 0;
}

void	reset_img(int width, int height, uint32_t colour, mlx_image_t *img)
{
	int	x;
	int	y;

	if (height == SCREEN_HEIGHT)
		y = height / 2;
	else
		y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (y >= 0 && y < height && x >= 0 && x < width)
				mlx_put_pixel(img, x, y, colour);
			x++;
		}
		y++;
	}
}

void render_3d_walls(t_player *player, t_rays *rays, mlx_image_t *wall_layer)
{
    ft_memset(wall_layer->pixels, 0, wall_layer->width * wall_layer->height * sizeof(int32_t));
    
    int ray_step = NUM_RAYS / SCREEN_WIDTH;
    ray_step = ray_step < 1 ? 1 : ray_step;
    
    for (int screen_x = 0; screen_x < SCREEN_WIDTH; screen_x++)
    {
        int ray_idx = (screen_x * NUM_RAYS) / SCREEN_WIDTH;
        ray_idx = ray_idx < 0 ? 0 : (ray_idx >= NUM_RAYS ? NUM_RAYS - 1 : ray_idx);

        if ((*rays)[ray_idx].distance <= 0)
            continue;

        float angle_diff = (*rays)[ray_idx].ray_angle - player->rotation_angle;
        float corrected_distance = (*rays)[ray_idx].distance * cos(angle_diff);
        
        corrected_distance = fmaxf(corrected_distance, 0.1f);
        
        float dist_to_proj_plane = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);
        float wall_height = (CUBE_SIZE / corrected_distance) * dist_to_proj_plane;
        
        int wall_top = (SCREEN_HEIGHT / 2) - (wall_height / 2);
        wall_top = wall_top < 0 ? 0 : wall_top;
        
        int wall_bottom = (SCREEN_HEIGHT / 2) + (wall_height / 2);
        wall_bottom = wall_bottom >= SCREEN_HEIGHT ? SCREEN_HEIGHT - 1 : wall_bottom;
        
        uint32_t color = 0xFFFFFFFF;
        
        for (int y = wall_top; y <= wall_bottom; y++)
        {
            if (y >= 0 && y < SCREEN_HEIGHT) {
                mlx_put_pixel(wall_layer, screen_x, y, color);
            }
        }
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
	ft_memset(game->wall_layer->pixels, 0, 
		game->wall_layer->width * game->wall_layer->height * sizeof(int32_t));
	ft_memset(game->dynamic_layer->pixels, 0, game->dynamic_layer->width
		* game->dynamic_layer->height * sizeof(int32_t));
	move_player(player);
	cast_all_rays(player, &rays);
	render_3d_walls(player, &rays, game->wall_layer);
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
    game->background_layer = NULL;
    game->window_width = 0;
    game->window_height = 0;
}

int main(int argc, char **argv)
{
    t_str_access stru_access;
    t_game *game;

    if (check_argc(argc, argv))
        return (1);

    initiate_str_access_values(&stru_access);
    game = stru_access.game;
    init_game(game);
    initiate_map(stru_access.map, argv[1], game);
    initiate_player(stru_access.player, game);
    stru_access.player->map = stru_access.map;
    init_mlx(game);
    mlx_image_to_window(game->mlx, game->background_layer, 0, 0);
	mlx_image_to_window(game->mlx, game->wall_layer, 0, 0);
    mlx_image_to_window(game->mlx, game->static_layer, 0, 0);
    mlx_image_to_window(game->mlx, game->dynamic_layer, 0, 0);
    add_static_pixels(&stru_access);
	reset_img(SCREEN_WIDTH, SCREEN_HEIGHT / 2, game->floor_color, game->background_layer);
	reset_img(SCREEN_WIDTH, SCREEN_HEIGHT, game->ceiling_color, game->background_layer);
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
// 	mlx_image_to_window(game->mlx, game->background_layer, 0, 0);
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

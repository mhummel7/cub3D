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
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		player->diagonal_direction = +1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		player->diagonal_direction = -1;
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
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		player->diagonal_direction = 0;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		player->diagonal_direction = 0;
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

uint32_t get_mlx_texture_color(mlx_texture_t* texture, int x, int y)
{
    if (!texture || x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
        return 0xFF000000;
    int index = (y * texture->width + x) * 4;
    uint8_t r = texture->pixels[index];
    uint8_t g = texture->pixels[index + 1];
    uint8_t b = texture->pixels[index + 2];
    uint8_t a = texture->pixels[index + 3];
    return (r << 24) | (g << 16) | (b << 8) | a;
}

void generate3Dprojection(t_rays *rays, t_player *player)
{
    int i = 0;
    while(i < NUM_RAYS)
    {
        float perpDistance = (*rays)[i].distance * cos((*rays)[i].ray_angle - player->rotation_angle);
        float distanceProjPlane = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);
        float projectedWallHeight = (CUBE_SIZE / perpDistance) * distanceProjPlane;
        int wallStripHeight = (int)projectedWallHeight;
        float wallX;
        if ((*rays)[i].was_hit_vertical)
            wallX = (*rays)[i].wall_hit_y - floor((*rays)[i].wall_hit_y);
        else
            wallX = (*rays)[i].wall_hit_x - floor((*rays)[i].wall_hit_x);
        mlx_texture_t* texture;
        if ((*rays)[i].was_hit_vertical) {
            texture = ((*rays)[i].ray_angle > M_PI/2 && (*rays)[i].ray_angle < 3*M_PI/2) 
                ? player->game->we_tex : player->game->ea_tex;
        } else {
            texture = ((*rays)[i].ray_angle > M_PI) 
                ? player->game->so_tex : player->game->no_tex;
        }
        int wallTopPixel = (SCREEN_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
        int wallBottomPixel = (SCREEN_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > SCREEN_HEIGHT ? SCREEN_HEIGHT : wallBottomPixel;
        int y = wallTopPixel;
        while(y < wallBottomPixel)
        {
            float texPosY = (y - wallTopPixel) / (float)wallStripHeight;
            int texY = (int)(texPosY * texture->height);
            texY = texY < 0 ? 0 : (texY >= (int)texture->height ? texture->height - 1 : texY);
            int texX = (int)(wallX * texture->width);
            texX = texX < 0 ? 0 : (texX >= (int)texture->width ? texture->width - 1 : texX);
            uint32_t color = get_mlx_texture_color(texture, texX, texY);
            mlx_put_pixel(player->game->wall_layer, i, y, color);
            y++;
        }
        i++;
    }
}

void clearColorBuffer(uint32_t color, t_game *game) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            mlx_put_pixel(game->wall_layer, x, y, color);
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
	ft_memset(game->dynamic_layer->pixels, 0, game->dynamic_layer->width
		* game->dynamic_layer->height * sizeof(int32_t));
	move_player(player);
	cast_all_rays(player, &rays);
	clearColorBuffer(0xFF000000, game);
	generate3Dprojection(&rays, player);
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

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
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

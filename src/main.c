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
void	init_preparsing_assets(t_game *game)
{
	game->assets = malloc (sizeof(t_assets));
	if (!game->assets)
		error_exit("Error alllocating assets");
	game->assets->no = NULL;
	game->assets->ea = NULL;
	game->assets->so = NULL;
	game->assets->we = NULL;
	game->assets->c = 0;
	game->assets->f = 0;
	game->assets->c_set = false;
	game->assets->f_set = false;
	game->assets->err = 0;
	game->assets->i = 0;
}

void	init_preparsing_map(t_game *game)
{
	game->map = NULL;

	game->map_height = 0;
	game->map_width = 0;
	game->pos_player.x = -1;
	game->pos_player.y = -1;
	game->dir_player.x = 0;
	game->dir_player.y = 0;
	game->mlx = NULL;
	game->dynamic_layer = NULL;
	game->static_layer = NULL;
	game->ray_dir.x = -1.0f; // Initial ray direction (facing left)
    game->ray_dir.y = 0.0f;
    game->plane.x = 0.0f;    // Initial camera plane (for FOV)
    game->plane.y = 0.66f;
}

int	is_coliding(t_game *game, float x, float y)
{
	float	pr;

	pr = 0.2;
	return (game->map[(int)(y + pr)][(int)(x + pr)] == '1' ||
		game->map[(int)(y + pr)][(int)(x - pr)] == '1' ||
		game->map[(int)(y - pr)][(int)(x + pr)] == '1' ||
		game->map[(int)(y - pr)][(int)(x - pr)] == '1');
}

void	rotation(t_game *game, float angle)
{
	float		old_plane_x;
	t_vector	dir;

	dir.x = game->dir_player.x * cos(angle) - game->dir_player.y * sin(angle);
	dir.y = game->dir_player.x * sin(angle) + game->dir_player.y * cos(angle);
	game->dir_player = dir;
	old_plane_x = game->plane.x;
	game->plane.x = game->plane.x * cos(angle) - game->plane.y * sin(angle);
	game->plane.y = old_plane_x * sin(angle) + game->plane.y * cos(angle);
}

void	update_position(t_game *game, float next_x, float next_y, int dir)
{
	if (dir == X_DIR)
	{
		game->pos_player.x = next_x;
	}
	else if (dir == Y_DIR)
	{
		game->pos_player.y = next_y;
	}
}

void	side_dir(t_game *game, int sideways, float *move_x, float *move_y)
{
	if (sideways)
	{
		*move_x = game->dir_player.y;
		*move_y = -game->dir_player.x;
	}
	else
	{
		*move_x = game->dir_player.x;
		*move_y = game->dir_player.y;
	}
}

void	two_keys_pressed(t_game *game, float *speed)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W)
		|| mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_D)
			|| mlx_is_key_down(game->mlx, MLX_KEY_A))
			*speed /= 2;
	}
}

void	movement(t_game *game, float speed, int sideways)
{
	float	next_x;
	float	next_y;
	float	move_x;
	float	move_y;

	side_dir(game, sideways, &move_x, &move_y);
	two_keys_pressed(game, &speed);
	next_x = game->pos_player.x + move_x * speed;
	next_y = game->pos_player.y + move_y * speed;
	if (!is_coliding(game, next_x, game->pos_player.y))
		update_position(game, next_x, game->pos_player.y, X_DIR);
	if (!is_coliding(game, game->pos_player.x, next_y))
		update_position(game, game->pos_player.x, next_y, Y_DIR);
}

void	handling_key_input(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(game->mlx);
    	free_game(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		movement(game, 0.07, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		movement(game, -0.07, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		movement(game, 0.07, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		movement(game, -0.07, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotation(game, -0.05);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotation(game, 0.05);
}

void	reset_img(int width, int height, uint32_t colour, mlx_image_t *img)
{
	int	x;
	int	y;

	if (height == HEIGHT)
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

void render(void *param)
{
    t_game *game = (t_game *)param;

    handling_key_input(game);
    reset_img(game->width, game->height / 2, game->assets->f, game->wall_image);
	reset_img(game->width, game->height, game->assets->c, game->wall_image);
}

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2 || !ft_strrchr(argv[1], '.') || ft_strcmp(ft_strrchr(argv[1], '.'), ".cub"))
        error_exit("Usage: ./cub3D <map.cub>");
    init_preparsing_assets(&game);
	init_preparsing_map(&game);
    parse_cub_file(argv[1], &game);
    init_mlx(&game);
    add_static_pixels(&game);
    mlx_loop_hook(game.mlx, render, &game);
    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
    free_game(&game);
    printf("Done.\n");
    return (0);
}

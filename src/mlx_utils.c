/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:41:05 by mhummel           #+#    #+#             */
/*   Updated: 2025/03/13 11:43:31 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Handles forward (W) and backward (S) movement
void	handle_movement(t_game *game, mlx_key_data_t keydata, double move_speed)
{
	double	new_x;
	double	new_y;

	if (keydata.key == MLX_KEY_W)
	{
		new_x = game->pos_player.x + game->dir_player.x * move_speed;
		new_y = game->pos_player.y + game->dir_player.y * move_speed;
		if (!check_collision(game, new_x, new_y))
		{
			game->pos_player.x = new_x;
			game->pos_player.y = new_y;
		}
	}
	else if (keydata.key == MLX_KEY_S)
	{
		new_x = game->pos_player.x - game->dir_player.x * move_speed;
		new_y = game->pos_player.y - game->dir_player.y * move_speed;
		if (!check_collision(game, new_x, new_y))
		{
			game->pos_player.x = new_x;
			game->pos_player.y = new_y;
		}
	}
}

// Handles strafing left (A) and right (D)
void	handle_strafe(t_game *game, mlx_key_data_t keydata, double move_speed)
{
	double	new_x;
	double	new_y;

	if (keydata.key == MLX_KEY_A)
	{
		new_x = game->pos_player.x + game->dir_player.y * move_speed; // Perpendicular to direction
		new_y = game->pos_player.y - game->dir_player.x * move_speed;
		if (!check_collision(game, new_x, new_y))
		{
			game->pos_player.x = new_x;
			game->pos_player.y = new_y;
		}
	}
	else if (keydata.key == MLX_KEY_D)
	{
		new_x = game->pos_player.x - game->dir_player.y * move_speed;
		new_y = game->pos_player.y + game->dir_player.x * move_speed;
		if (!check_collision(game, new_x, new_y))
		{
			game->pos_player.x = new_x;
			game->pos_player.y = new_y;
		}
	}
}

void init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	game->dynamic_layer = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->static_layer = mlx_new_image(game->mlx, WIDTH, HEIGHT);
}

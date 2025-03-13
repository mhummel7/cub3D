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
		new_x = game->pos_x + game->dir_x * move_speed;
		new_y = game->pos_y + game->dir_y * move_speed;
		if (!check_collision(game, new_x, new_y))
		{
			game->pos_x = new_x;
			game->pos_y = new_y;
		}
	}
	else if (keydata.key == MLX_KEY_S)
	{
		new_x = game->pos_x - game->dir_x * move_speed;
		new_y = game->pos_y - game->dir_y * move_speed;
		if (!check_collision(game, new_x, new_y))
		{
			game->pos_x = new_x;
			game->pos_y = new_y;
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
		new_x = game->pos_x + game->dir_y * move_speed; // Perpendicular to direction
		new_y = game->pos_y - game->dir_x * move_speed;
		if (!check_collision(game, new_x, new_y))
		{
			game->pos_x = new_x;
			game->pos_y = new_y;
		}
	}
	else if (keydata.key == MLX_KEY_D)
	{
		new_x = game->pos_x - game->dir_y * move_speed;
		new_y = game->pos_y + game->dir_x * move_speed;
		if (!check_collision(game, new_x, new_y))
		{
			game->pos_x = new_x;
			game->pos_y = new_y;
		}
	}
}

// Rotates player direction left or right
void	handle_rotation(t_game *game, mlx_key_data_t keydata, double rot_speed)
{
	double	old_dir_x;

	if (keydata.key == MLX_KEY_LEFT)
	{
		old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(rot_speed) - game->dir_y * sin(rot_speed);
		game->dir_y = old_dir_x * sin(rot_speed) + game->dir_y * cos(rot_speed);
	}
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(-rot_speed) - game->dir_y * sin(-rot_speed);
		game->dir_y = old_dir_x * sin(-rot_speed) + game->dir_y * cos(-rot_speed);
	}
}

void init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	game->dynamic_layer = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->static_layer = mlx_new_image(game->mlx, WIDTH, HEIGHT);
}

// Updates player based on held keys
void update_player(t_game *game, double move_speed, double rot_speed)
{
	mlx_key_data_t keydata = {0}; // Fully initialize struct
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		keydata.key = MLX_KEY_W;
		handle_movement(game, keydata, move_speed);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		keydata.key = MLX_KEY_S;
		handle_movement(game, keydata, move_speed);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		keydata.key = MLX_KEY_A;
		handle_strafe(game, keydata, move_speed);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		keydata.key = MLX_KEY_D;
		handle_strafe(game, keydata, move_speed);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		keydata.key = MLX_KEY_LEFT;
		handle_rotation(game, keydata, rot_speed);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		keydata.key = MLX_KEY_RIGHT;
		handle_rotation(game, keydata, rot_speed);
	}
}

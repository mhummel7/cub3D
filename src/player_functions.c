/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:04:10 by frocha            #+#    #+#             */
/*   Updated: 2025/04/11 11:25:27 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_player(t_player *player)
{
	float	move_step;
	float	side_step;
	float	move_x;
	float	move_y;
	float	new_x;
	float	new_y;

	player->rotation_angle += player->turn_direction * player->turn_speed;
	move_step = player->walk_direction * player->walk_speed;
	side_step = player->diagonal_direction * player->walk_speed;
	move_x = cos(player->rotation_angle) * move_step
		+ cos(player->rotation_angle - PI / 2) * side_step;
	move_y = sin(player->rotation_angle) * move_step
		+ sin(player->rotation_angle - PI / 2) * side_step;
	new_x = player->x;
	new_y = player->y;
	if (!check_obstacle_blocks(player->x + move_x, player->y, player))
		new_x += move_x;
	if (!check_obstacle_blocks(player->x, player->y + move_y, player))
		new_y += move_y;
	if (new_x != player->x || new_y != player->y)
	{
		player->x = new_x;
		player->y = new_y;
	}
}

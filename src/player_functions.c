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
	t_move_player_vars	vars;

	player->rotation_angle += player->turn_direction * player->turn_speed;
	vars.move_step = player->walk_direction * player->walk_speed;
	vars.side_step = player->diagonal_direction * player->walk_speed;
	vars.move_x = cos(player->rotation_angle) * vars.move_step
		+ cos(player->rotation_angle - PI / 2) * vars.side_step;
	vars.move_y = sin(player->rotation_angle) * vars.move_step
		+ sin(player->rotation_angle - PI / 2) * vars.side_step;
	vars.new_x = player->x;
	vars.new_y = player->y;
	if (!check_obstacle_blocks(player->x + vars.move_x, player->y, player))
		vars.new_x += vars.move_x;
	if (!check_obstacle_blocks(player->x, player->y + vars.move_y, player))
		vars.new_y += vars.move_y;
	if (vars.new_x != player->x || vars.new_y != player->y)
	{
		player->x = vars.new_x;
		player->y = vars.new_y;
	}
}

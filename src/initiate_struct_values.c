/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_struct_values.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:03:49 by frocha            #+#    #+#             */
/*   Updated: 2025/04/03 13:02:51 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	initiate_map(t_map *map, char *filename, t_game *game)
{
	parse_cub_file(filename, game);
	map->grid = game->map;
	map->map_height = game->map_height;
	map->map_width = game->map_width;
    printf("After initiate_map: map->map_height = %d\n", map->map_height);
}

void	initiate_player(t_player *player, t_game *game)
{
	player->x = 0;
	player->y = 0;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = PI / 2;
	player->walk_speed = 2;
	player->turn_speed = 2 * (PI / 180);
	player->game = game;
}

void	initiate_str_access_values(t_str_access *str_access)
{
	str_access->game = malloc(sizeof(t_game));
	str_access->map = malloc(sizeof(t_map));
	str_access->player = malloc(sizeof(t_player));
}

void	set_player_rotation_angle(t_player *player, char letter)
{
	if (letter == 'N')
	{
		player->rotation_angle = PI * 1.5;
	}
	else if (letter == 'S')
	{
		player->rotation_angle = PI / 2;
	}
	else if (letter == 'E')
	{
		player->rotation_angle = 0;
	}
	else if (letter == 'W')
	{
		player->rotation_angle = PI;
	}
}

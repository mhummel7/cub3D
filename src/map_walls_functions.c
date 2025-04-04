/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:04:02 by frocha            #+#    #+#             */
/*   Updated: 2025/04/03 13:03:18 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_walls(t_game *game, int base_x_mult, int base_y_mult)
{
	int	x;
	int	y;

	y = 0;
	while (y < CUBE_SIZE)
	{
		x = 0;
		while (x < CUBE_SIZE)
		{
			mlx_put_pixel(game->static_layer, base_x_mult + x, base_y_mult + y,
				0xFFFFFFFF);
			x++;
		}
		y++;
	}
}

void	process_map_row(t_str_access *str_access, int i, int *base_x_mult,
		int *base_y_mult)
{
	int			x;
	t_player	*player;
	t_map		*map;
	t_game		*game;

	player = str_access->player;
	map = str_access->map;
	game = str_access->game;
	x = 0;
	while (map->grid[i][x])
	{
		if (map->grid[i][x] == '1')
		{
			draw_walls(game, *base_x_mult, *base_y_mult);
		}
		else if (map->grid[i][x] == 'N' || map->grid[i][x] == 'S'
			|| map->grid[i][x] == 'E' || map->grid[i][x] == 'W')
		{
			player->x = game->pos_x * CUBE_SIZE;
			player->y = game->pos_y * CUBE_SIZE;
			set_player_rotation_angle(player, map->grid[i][x]);
		}
		*base_x_mult += CUBE_SIZE;
		x++;
	}
}

void	add_static_pixels(t_str_access *str_access)
{
	int	add_y;
	int	base_x_mult;
	int	base_y_mult;
	int	i;

	add_y = 0;
	base_x_mult = 0;
	base_y_mult = 0;
	i = 0;
	while (i < str_access->map->map_height)
	{
		process_map_row(str_access, i, &base_x_mult, &base_y_mult);
		add_y++;
		base_x_mult = 0;
		base_y_mult = CUBE_SIZE * add_y;
		i++;
	}
}

int	check_obstacle_blocks(float new_player_x, float new_player_y,
		t_player *player)
{
	t_map	*map;
	int		column_block;
	int		row_block;

	column_block = (new_player_x / CUBE_SIZE);
	row_block = (new_player_y / CUBE_SIZE);
	map = player->map;
	if (row_block < 0 || row_block >= map->map_height || column_block < 0
		|| column_block >= map->map_width)
	{
		return (1);
	}
	if (map->grid[row_block][column_block] == '1')
	{
		return (1);
	}
	return (0);
}

int	is_wall(float x, float y, t_player *player)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	if (x < 0 || x > player->game->window_width || y < 0
		|| y > player->game->window_height)
		return (1);
	map_grid_index_x = floor(x / CUBE_SIZE);
	map_grid_index_y = floor(y / CUBE_SIZE);
	if (player->map->grid[map_grid_index_y][map_grid_index_x] == '1')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

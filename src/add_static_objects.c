/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_static_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:41:01 by frocha            #+#    #+#             */
/*   Updated: 2025/03/19 15:41:03 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_walls(t_game *game, int base_x_mult, int base_y_mult)
{
    int x;
    int y;

    y = 0;
    while (y < CUBE_SIZE)
    {
        x = 0;
        while (x < CUBE_SIZE)
        {
            mlx_put_pixel(game->static_layer, base_x_mult + x, base_y_mult + y, 0xFFFFFFFF); // White color
            x++;
        }
        y++;
    }
}

void	assigne_angle_dir(t_game *game, float angle, float x, float y)
{
	game->player_angle = angle;
	game->plane.x = x;
	game->plane.y = y;
}

void set_player_location(t_game *game, int base_x_mult, int base_y_mult, char cell)
{
    game->pos_player.x = base_x_mult;
    game->pos_player.y = base_y_mult;
    if (cell == 'N')
		assigne_angle_dir(game, 3 * PI / 2, 0.66, 0);
	else if (cell == 'E')
		assigne_angle_dir(game, 0, 0, 0.66);
	else if (cell == 'S')
		assigne_angle_dir(game, PI / 2, -0.66, 0);
	else if (cell == 'W')
		assigne_angle_dir(game, PI, 0, -0.66);
	game->dir_player.x = cos(game->player_angle);
	game->dir_player.y = sin(game->player_angle);
}

void process_map_row(t_game *game, int i, int *base_x_mult, int *base_y_mult)
{
    int x;
    
    x = 0;
    while (game->map[i][x])
    {
        if (game->map[i][x] == '1')
        {
            draw_walls(game, *base_x_mult, *base_y_mult);
        }
        else
        {
            set_player_location(game, *base_x_mult, *base_y_mult, game->map[i][x]);
        }
        *base_x_mult += CUBE_SIZE;
        x++;
    }
}

void add_static_pixels(t_game *game)
{
    int add_y;
    int base_x_mult;
    int base_y_mult;
    int i;

    add_y = 1;
    base_x_mult = CUBE_SIZE;
    base_y_mult = CUBE_SIZE;
    i = 0;
    while (i < game->map_height)
    {
        process_map_row(game, i, &base_x_mult, &base_y_mult);
        add_y++;
        base_x_mult = CUBE_SIZE;
        base_y_mult = CUBE_SIZE * add_y;
        i++;
    }
    mlx_image_to_window(game->mlx, game->static_layer, 0, 0);
}
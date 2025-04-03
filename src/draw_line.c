/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:03:24 by frocha            #+#    #+#             */
/*   Updated: 2025/04/02 17:01:04 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void initialize_values(t_player *player, t_draw_line_variables *vars, float dest_x, float dest_y)
{
    vars->init_x = (int)player->x;
    vars->init_y = (int)player->y;
    vars->dest_x = (int)dest_x;
    vars->dest_y = (int)dest_y;
    vars->dx = abs(vars->dest_x - vars->init_x);
    vars->dy = -abs(vars->dest_y - vars->init_y);
    vars->sx = -1;
    vars->sy = -1;
    if (vars->init_x < vars->dest_x)
        vars->sx = 1;
    if (vars->init_y < vars->dest_y)
        vars->sy = 1;
    vars->err = vars->dx + vars->dy;
}

void draw_line(t_player *player, t_game *game, float dest_x, float dest_y)
{
    t_draw_line_variables vars;

    initialize_values(player, &vars, dest_x, dest_y);
    while (1)
    {
        // Prüfe Grenzen
        if (vars.init_x >= 0 && vars.init_x < game->window_width && vars.init_y >= 0 && vars.init_y < game->window_height)
            mlx_put_pixel(game->dynamic_layer, vars.init_x, vars.init_y, 0xFF0000FF);
        if (vars.init_x == vars.dest_x && vars.init_y == vars.dest_y)
            break;
        vars.e2 = 2 * vars.err;
        if (vars.e2 >= vars.dy)
        {
            vars.err += vars.dy;
            vars.init_x += vars.sx;
        }
        if (vars.e2 <= vars.dx)
        {
            vars.err += vars.dx;
            vars.init_y += vars.sy;
        }
    }
}

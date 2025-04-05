/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:53:06 by frocha            #+#    #+#             */
/*   Updated: 2025/04/04 22:53:07 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void generate_3d_projection(t_rays *rays, t_player *player)
{
    int i = 0;
    while(i < NUM_RAYS)
    {
        float perp_distance = (*rays)[i].distance * cos((*rays)[i].ray_angle - player->rotation_angle);
        float distance_proj_plane = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);
        float projected_wall_height = (CUBE_SIZE / perp_distance) * distance_proj_plane;
        int wall_strip_height = (int)projected_wall_height;
        float wallX;
        if ((*rays)[i].was_hit_vertical)
            wallX = (*rays)[i].wall_hit_y - floor((*rays)[i].wall_hit_y);
        else
            wallX = (*rays)[i].wall_hit_x - floor((*rays)[i].wall_hit_x);
        mlx_texture_t* texture;
        if ((*rays)[i].was_hit_vertical) {
            texture = ((*rays)[i].ray_angle > PI/2 && (*rays)[i].ray_angle < 3*PI/2) 
                ? player->game->we_tex : player->game->ea_tex;
        } else {
            texture = ((*rays)[i].ray_angle > PI) 
                ? player->game->so_tex : player->game->no_tex;
        }
        int wall_top_pixel = (SCREEN_HEIGHT / 2) - (wall_strip_height / 2);
        wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
        int wall_bottom_pixel = (SCREEN_HEIGHT / 2) + (wall_strip_height / 2);
        wall_bottom_pixel = wall_bottom_pixel > SCREEN_HEIGHT ? SCREEN_HEIGHT : wall_bottom_pixel;
        int y = wall_top_pixel;
        while(y < wall_bottom_pixel)
        {
            float tex_pos_y = (y - wall_top_pixel) / (float)wall_strip_height;
            int tex_y = (int)(tex_pos_y * texture->height);
            tex_y = tex_y < 0 ? 0 : (tex_y >= (int)texture->height ? texture->height - 1 : tex_y);
            int tex_x = (int)(wallX * texture->width);
            tex_x = tex_x < 0 ? 0 : (tex_x >= (int)texture->width ? texture->width - 1 : tex_x);
            uint32_t color = get_mlx_texture_color(texture, tex_x, tex_y);
            mlx_put_pixel(player->game->wall_layer, i, y, color);
            y++;
        }
        i++;
    }
}
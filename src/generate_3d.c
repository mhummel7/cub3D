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
        float perpDistance = (*rays)[i].distance * cos((*rays)[i].ray_angle - player->rotation_angle);
        float distanceProjPlane = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);
        float projectedWallHeight = (CUBE_SIZE / perpDistance) * distanceProjPlane;
        int wallStripHeight = (int)projectedWallHeight;
        float wallX;
        if ((*rays)[i].was_hit_vertical)
            wallX = (*rays)[i].wall_hit_y - floor((*rays)[i].wall_hit_y);
        else
            wallX = (*rays)[i].wall_hit_x - floor((*rays)[i].wall_hit_x);
        mlx_texture_t* texture;
        if ((*rays)[i].was_hit_vertical) {
            texture = ((*rays)[i].ray_angle > M_PI/2 && (*rays)[i].ray_angle < 3*M_PI/2) 
                ? player->game->we_tex : player->game->ea_tex;
        } else {
            texture = ((*rays)[i].ray_angle > M_PI) 
                ? player->game->so_tex : player->game->no_tex;
        }
        int wallTopPixel = (SCREEN_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
        int wallBottomPixel = (SCREEN_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > SCREEN_HEIGHT ? SCREEN_HEIGHT : wallBottomPixel;
        int y = wallTopPixel;
        while(y < wallBottomPixel)
        {
            float texPosY = (y - wallTopPixel) / (float)wallStripHeight;
            int texY = (int)(texPosY * texture->height);
            texY = texY < 0 ? 0 : (texY >= (int)texture->height ? texture->height - 1 : texY);
            int texX = (int)(wallX * texture->width);
            texX = texX < 0 ? 0 : (texX >= (int)texture->width ? texture->width - 1 : texX);
            uint32_t color = get_mlx_texture_color(texture, texX, texY);
            mlx_put_pixel(player->game->wall_layer, i, y, color);
            y++;
        }
        i++;
    }
}
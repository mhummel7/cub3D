/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:53:06 by frocha            #+#    #+#             */
/*   Updated: 2025/04/14 10:09:44 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

uint32_t	get_mlx_texture_color(mlx_texture_t *texture, int x, int y)
{
	int		index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (!texture || x < 0 || x >= (int)texture->width || y < 0
		|| y >= (int)texture->height)
		return (0xFF000000);
	index = (y * texture->width + x) * 4;
	r = texture->pixels[index];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	a = texture->pixels[index + 3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	put_pixels(t_process_single_ray_variables *vars, t_player *player,
		int x, mlx_texture_t *texture)
{
	uint32_t	color;

	vars->tex_pos_y = vars->y + (vars->wall_strip_height / 2) - (SCREEN_HEIGHT
			/ 2);
	vars->tex_y = (int)(vars->tex_pos_y * ((float)texture->height
				/ vars->wall_strip_height));
	if (vars->tex_y < 0)
		vars->tex_y = 0;
	else if (vars->tex_y >= (int)texture->height)
		vars->tex_y = texture->height - 1;
	vars->tex_x = (int)(vars->wall_x * texture->width);
	if (vars->tex_x < 0)
		vars->tex_x = 0;
	else if (vars->tex_x >= (int)texture->width)
		vars->tex_x = texture->width - 1;
	color = get_mlx_texture_color(texture, vars->tex_x, vars->tex_y);
	mlx_put_pixel(player->game->wall_layer, x, vars->y, color);
}

void	set_top_bottom_pixel(t_process_single_ray_variables *vars,
		t_player *player, int x, t_rays *rays)
{
	if (!(*rays)[x].was_hit_vertical)
	{
		if ((*rays)[x].ray_angle > PI)
			vars->texture = player->game->so_tex;
		else
			vars->texture = player->game->no_tex;
	}
	vars->wall_top_pixel = (SCREEN_HEIGHT / 2) - (vars->wall_strip_height / 2);
	if (vars->wall_top_pixel < 0)
		vars->wall_top_pixel = 0;
	vars->wall_bottom_pixel = (SCREEN_HEIGHT / 2) + (vars->wall_strip_height
			/ 2);
	if (vars->wall_bottom_pixel > SCREEN_HEIGHT)
		vars->wall_bottom_pixel = SCREEN_HEIGHT;
	vars->y = vars->wall_top_pixel;
	while (vars->y < vars->wall_bottom_pixel)
	{
		put_pixels(vars, player, x, vars->texture);
		vars->y++;
	}
}

void	process_single_ray(t_rays *rays, int x, t_player *player)
{
	t_process_single_ray_variables	vars;

	vars.perp_distance = (*rays)[x].distance * cos((*rays)[x].ray_angle
			- player->rotation_angle);
	vars.distance_proj_plane = (SCREEN_WIDTH / 2) / tan((60 * (PI / 180)) / 2);
	vars.projected_wall_height = (CUBE_SIZE / vars.perp_distance)
		* vars.distance_proj_plane;
	vars.wall_strip_height = (int)vars.projected_wall_height;
	if ((*rays)[x].was_hit_vertical)
		vars.wall_x = fmod((*rays)[x].wall_hit_y, CUBE_SIZE) / CUBE_SIZE;
	else
		vars.wall_x = fmod((*rays)[x].wall_hit_x, CUBE_SIZE) / CUBE_SIZE;
	if ((*rays)[x].was_hit_vertical)
	{
		if ((*rays)[x].ray_angle > PI / 2 && (*rays)[x].ray_angle < 3 * PI / 2)
			vars.texture = player->game->we_tex;
		else
			vars.texture = player->game->ea_tex;
	}
	set_top_bottom_pixel(&vars, player, x, rays);
}

void	generate_3d_projection(t_rays *rays, t_player *player)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		process_single_ray(rays, i, player);
		i++;
	}
}

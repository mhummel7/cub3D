/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ray_between_limits.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:56:17 by frocha            #+#    #+#             */
/*   Updated: 2025/04/03 12:51:36 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	check_limits_horz_ray(t_ray_wall_hit_horz *horz_ray_data, t_game *game)
{
	if (horz_ray_data->next_horz_touch_wall_x >= 0
		&& horz_ray_data->next_horz_touch_wall_x < game->window_width
		&& horz_ray_data->next_horz_touch_wall_y >= 0
		&& horz_ray_data->next_horz_touch_wall_y < game->window_height)
	{
		return (true);
	}
	return (false);
}

bool	check_limits_vert_ray(t_ray_wall_hit_vert *vert_ray_data, t_game *game)
{
	if (vert_ray_data->next_vert_touch_wall_x >= 0
		&& vert_ray_data->next_vert_touch_wall_x <= game->window_width
		&& vert_ray_data->next_vert_touch_wall_y >= 0
		&& vert_ray_data->next_vert_touch_wall_y <= game->window_height)
	{
		return (true);
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir_player_pos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:03:56 by frocha            #+#    #+#             */
/*   Updated: 2025/04/04 22:03:57 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_dir_player_pos(t_game *game, int x, int y)
{
	game->dir_x = x;
	game->dir_y = y;
}

int	set_texture_direction(char **texture_char, mlx_texture_t **texture,
		char *value)
{
	*(texture_char) = ft_strdup(value);
	*(texture) = mlx_load_png(value);
	if (!*(texture))
		return (0);
	return (1);
}

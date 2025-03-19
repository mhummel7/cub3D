/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:41:05 by mhummel           #+#    #+#             */
/*   Updated: 2025/03/13 11:43:31 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void init_mlx(t_game *game)
{
	game->width = WIDTH;
	game->height = HEIGHT;
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	game->dynamic_layer = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->static_layer = mlx_new_image(game->mlx, WIDTH, HEIGHT);
}

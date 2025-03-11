/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:17 by mhummel           #+#    #+#             */
/*   Updated: 2025/03/11 11:29:39 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	if (game->no_texture)
		free(game->no_texture);
	if (game->so_texture)
		free(game->so_texture);
	if (game->we_texture)
		free(game->we_texture);
	if (game->ea_texture)
		free(game->ea_texture);
		if (game->no_tex)
        mlx_delete_texture(game->no_tex);
    if (game->so_tex)
        mlx_delete_texture(game->so_tex);
    if (game->we_tex)
        mlx_delete_texture(game->we_tex);
    if (game->ea_tex)
        mlx_delete_texture(game->ea_tex);
	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
		{
			printf("Freeing map[%d]: %p\n", i, game->map[i]); // Debug message
			if (game->map[i])
				free(game->map[i]);
			i++;
		}
		printf("Freeing map array: %p\n", game->map); // Debug message
		free(game->map);
	}
}

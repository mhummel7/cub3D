/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:17 by mhummel           #+#    #+#             */
/*   Updated: 2025/04/07 12:33:56 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_game_char(t_game *game)
{
	if (game->no_texture)
		free(game->no_texture);
	if (game->so_texture)
		free(game->so_texture);
	if (game->we_texture)
		free(game->we_texture);
	if (game->ea_texture)
		free(game->ea_texture);
}

void	free_game_textures(t_game *game)
{
	if (game->no_tex)
		mlx_delete_texture(game->no_tex);
	if (game->so_tex)
		mlx_delete_texture(game->so_tex);
	if (game->we_tex)
		mlx_delete_texture(game->we_tex);
	if (game->ea_tex)
		mlx_delete_texture(game->ea_tex);
}

void	free_game(t_game *game)
{
	int	i;

	if (game->filename)
		free(game->filename);
	free_game_char(game);
	free_game_textures(game);
	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
}

void	free_str_access(t_str_access *str_access)
{
	if (str_access->player)
		free(str_access->player);
	if (str_access->map)
		free(str_access->map);
	if (str_access->game)
		free(str_access->game);
}

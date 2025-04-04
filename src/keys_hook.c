/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:56:54 by frocha            #+#    #+#             */
/*   Updated: 2025/04/04 22:56:55 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_release(t_player *player, mlx_key_data_t *keydata)
{
	if (keydata->key == MLX_KEY_W && (keydata->action == MLX_RELEASE))
		player->walk_direction = 0;
	else if (keydata->key == MLX_KEY_S && (keydata->action == MLX_RELEASE))
		player->walk_direction = 0;
	else if (keydata->key == MLX_KEY_LEFT && (keydata->action == MLX_RELEASE))
		player->turn_direction = 0;
	else if (keydata->key == MLX_KEY_RIGHT && (keydata->action == MLX_RELEASE))
		player->turn_direction = 0;
	if (keydata->key == MLX_KEY_A && (keydata->action == MLX_RELEASE))
		player->diagonal_direction = 0;
	else if (keydata->key == MLX_KEY_D && (keydata->action == MLX_RELEASE))
		player->diagonal_direction = 0;
}

void	keys_hook(mlx_key_data_t keydata, void *param)
{
	t_player	*player;

	player = (t_player *)param;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
		player->walk_direction = +1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		player->walk_direction = -1;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		player->diagonal_direction = +1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		player->diagonal_direction = -1;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS))
		player->turn_direction = -1;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS))
		player->turn_direction = +1;
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(player->game->mlx);
	set_release(player, &keydata);
}

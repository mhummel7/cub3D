/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:39:36 by frocha            #+#    #+#             */
/*   Updated: 2025/04/02 17:04:58 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	reset_img(int width, int height, uint32_t colour, mlx_image_t *img)
{
	int	x;
	int	y;

	if (height == SCREEN_HEIGHT)
		y = height / 2;
	else
		y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (y >= 0 && y < height && x >= 0 && x < width)
				mlx_put_pixel(img, x, y, colour);
			x++;
		}
		y++;
	}
}

void	clear_color_buffer(uint32_t color, t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			mlx_put_pixel(game->wall_layer, x, y, color);
			y++;
		}
		x++;
	}
}

void	render(void *param)
{
	t_str_access	*str_access;
	t_game			*game;
	t_player		*player;
	t_rays			rays;

	str_access = (t_str_access *)param;
	str_access = (t_str_access *)param;
	game = str_access->game;
	player = str_access->player;
	ft_memset(game->dynamic_layer->pixels, 0, game->dynamic_layer->width
		* game->dynamic_layer->height * sizeof(int32_t));
	move_player(player);
	cast_all_rays(player, &rays);
	clear_color_buffer(0xFF000000, game);
	generate_3d_projection(&rays, player);
	render_rays(player, &rays);
}

int	check_argc(int argc, char **argv)
{
	if (argc != 2 || !ft_strrchr(argv[1], '.') || ft_strcmp(ft_strrchr(argv[1],
				'.'), ".cub"))
	{
		write(2, "Error: Usage: ./cub3D <map.cub>\n", 32);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_str_access	stru_access;
	t_game			*game;

	if (check_argc(argc, argv))
		return (1);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	initiate_str_access_values(&stru_access);
	game = stru_access.game;
	init_game(game);
	initiate_map(stru_access.map, argv[1], game);
	initiate_player(stru_access.player, game);
	stru_access.player->map = stru_access.map;
	init_mlx(game);
	init_img_to_window(game);
	add_static_pixels(&stru_access);
	reset_img(SCREEN_WIDTH, SCREEN_HEIGHT / 2, game->floor_color,
		game->background_layer);
	reset_img(SCREEN_WIDTH, SCREEN_HEIGHT, game->ceiling_color,
		game->background_layer);
	mlx_loop_hook(game->mlx, render, &stru_access);
	mlx_key_hook(game->mlx, keys_hook, stru_access.player);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	return (0);
}

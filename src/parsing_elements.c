/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:27:50 by mhummel           #+#    #+#             */
/*   Updated: 2025/03/11 12:03:26 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	get_rgb(char *line)
{
	char	**split;

	int r, g, b;
	split = ft_split(line, ',');
	if (!split[0] || !split[1] || !split[2] || split[3])
		error_exit("Invalid RGB format");
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit("RGB values must be in range [0,255]");
	free_split(split);
	return (r << 24 | g << 16 | b << 8 | 255);
}

static void	set_texture(t_game *game, char *id, char *value)
{
	int	fd;

	fd = open(value, O_RDONLY);
	if (fd < 0)
		error_exit("Texture file not found");
	close(fd);
	if (ft_strcmp(id, "NO") == 0)
	{
		game->no_texture = ft_strdup(value);
		game->no_tex = mlx_load_png(value);
		if (!game->no_tex)
			error_exit("Failed to load NO texture");
		printf("Allocated no_texture: %p, Loaded no_tex: %p\n",
			game->no_texture, game->no_tex);
	}
	else if (ft_strcmp(id, "SO") == 0)
	{
		game->so_texture = ft_strdup(value);
		game->so_tex = mlx_load_png(value);
		if (!game->so_tex)
			error_exit("Failed to load SO texture");
		printf("Allocated so_texture: %p, Loaded so_tex: %p\n",
			game->so_texture, game->so_tex);
	}
	else if (ft_strcmp(id, "WE") == 0)
	{
		game->we_texture = ft_strdup(value);
		game->we_tex = mlx_load_png(value);
		if (!game->we_tex)
			error_exit("Failed to load WE texture");
		printf("Allocated we_texture: %p, Loaded we_tex: %p\n",
			game->we_texture, game->we_tex);
	}
	else if (ft_strcmp(id, "EA") == 0)
	{
		game->ea_texture = ft_strdup(value);
		game->ea_tex = mlx_load_png(value);
		if (!game->ea_tex)
			error_exit("Failed to load EA texture");
		printf("Allocated ea_texture: %p, Loaded ea_tex: %p\n",
			game->ea_texture, game->ea_tex);
	}
	else
		error_exit("Unknown element identifier");
}

void	parse_element(t_game *game, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split[0] || !split[1] || split[2])
		error_exit("Invalid element format");
	if (ft_strcmp(split[0], "F") == 0)
		game->floor_color = get_rgb(split[1]);
	else if (ft_strcmp(split[0], "C") == 0)
		game->ceiling_color = get_rgb(split[1]);
	else
		set_texture(game, split[0], split[1]);
	free_split(split);
}

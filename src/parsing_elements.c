/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:27:50 by mhummel           #+#    #+#             */
/*   Updated: 2025/03/06 12:42:01 by mhummel          ###   ########.fr       */
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
	return (r << 16 | g << 8 | b);
}

static void	set_texture(t_game *game, char *id, char *value)
{
	if (ft_strcmp(id, "NO") == 0)
	{
		game->no_texture = ft_strdup(value);
		printf("Allocated no_texture: %p\n", game->no_texture);
	}
	else if (ft_strcmp(id, "SO") == 0)
	{
		game->so_texture = ft_strdup(value);
		printf("Allocated so_texture: %p\n", game->so_texture);
	}
	else if (ft_strcmp(id, "WE") == 0)
	{
		game->we_texture = ft_strdup(value);
		printf("Allocated we_texture: %p\n", game->we_texture);
	}
	else if (ft_strcmp(id, "EA") == 0)
	{
		game->ea_texture = ft_strdup(value);
		printf("Allocated ea_texture: %p\n", game->ea_texture);
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

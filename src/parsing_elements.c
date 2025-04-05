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
	int		r;
	int		g;
	int		b;

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

void	validate_texture_path(char *path)
{
	int	fd;

	if (!path || !*path)
		error_exit("Empty texture path");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Texture file not found");
	close(fd);
}

void	set_texture(t_game *game, char *id, char *value)
{
	validate_texture_path(value);
	if (ft_strcmp(id, "NO") == 0)
	{
		if (!set_texture_direction(&(game->no_texture), &(game->no_tex), value))
			error_exit("Failed to load NO texture");
	}
	else if (ft_strcmp(id, "SO") == 0)
	{
		if (!set_texture_direction(&(game->so_texture), &(game->so_tex), value))
			error_exit("Failed to load SO texture");
	}
	else if (ft_strcmp(id, "WE") == 0)
	{
		if (!set_texture_direction(&(game->we_texture), &(game->we_tex), value))
			error_exit("Failed to load WE texture");
	}
	else if (ft_strcmp(id, "EA") == 0)
	{
		if (!set_texture_direction(&(game->ea_texture), &(game->ea_tex), value))
			error_exit("Failed to load EA texture");
	}
	else
		error_exit("Unknown element identifier");
}

void	parse_element(t_game *game, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	printf("AA:%s\n", split[0]);
	printf("AA:%s\n", split[1]);
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

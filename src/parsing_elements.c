/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:27:50 by mhummel           #+#    #+#             */
/*   Updated: 2025/04/11 11:14:55 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	validate_texture_path(char *path, t_game *game)
{
	int	fd;

	if (!path || !*path)
		error_exit_game("Empty texture path", game);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit_game("Texture file not found", game);
	close(fd);
}

void check_duplicate_texture(t_game *game, char *id)
{
    if (ft_strcmp(id, "NO") == 0 && game->no_texture)
        error_exit_game("Duplicate NO texture definition", game);
    if (ft_strcmp(id, "SO") == 0 && game->so_texture)
        error_exit_game("Duplicate SO texture definition", game);
    if (ft_strcmp(id, "WE") == 0 && game->we_texture)
        error_exit_game("Duplicate WE texture definition", game);
    if (ft_strcmp(id, "EA") == 0 && game->ea_texture)
        error_exit_game("Duplicate EA texture definition", game);
}

void	set_texture(t_game *game, char *id, char *value)
{
	validate_texture_path(value, game);
	check_duplicate_texture(game, id);
	if (ft_strcmp(id, "NO") == 0)
	{
		if (!set_texture_direction(&(game->no_texture), &(game->no_tex), value))
			error_exit_game("Failed to load NO texture", game);
	}
	else if (ft_strcmp(id, "SO") == 0)
	{
		if (!set_texture_direction(&(game->so_texture), &(game->so_tex), value))
			error_exit_game("Failed to load SO texture", game);
	}
	else if (ft_strcmp(id, "WE") == 0)
	{
		if (!set_texture_direction(&(game->we_texture), &(game->we_tex), value))
			error_exit_game("Failed to load WE texture", game);
	}
	else if (ft_strcmp(id, "EA") == 0)
	{
		if (!set_texture_direction(&(game->ea_texture), &(game->ea_tex), value))
			error_exit_game("Failed to load EA texture", game);
	}
	else
		error_exit_game("Unknown element identifier", game);
}

int	check_length(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		i++;
	}
	return (i);
}

void check_duplicate_color(t_game *game, char *id)
{
    if (ft_strcmp(id, "F") == 0 && game->floor_color != 0xFFFFFFFF)
        error_exit_game("Duplicate floor color definition", game);
    if (ft_strcmp(id, "C") == 0 && game->ceiling_color != 0xFFFFFFFF)
        error_exit_game("Duplicate ceiling color definition", game);
}

void parse_element(t_game *game, char *line)
{
    char    *processed_line;
    char    **split;

    processed_line = ft_strtrim(line, "\t,");
    if (!processed_line)
        error_exit("Memory allocation failed");
    split = ft_split(processed_line, ' ');
    free(processed_line);
    if (!split[0] || !split[1] || check_length(split) > 4)
        error_exit_game("Invalid element format", game);
    if (ft_strcmp(split[0], "F") == 0 || ft_strcmp(split[0], "C") == 0)
    {
        check_duplicate_color(game, split[0]);
        if (ft_strcmp(split[0], "F") == 0)
            game->floor_color = get_rgb(split + 1);
        else
            game->ceiling_color = get_rgb(split + 1);
    }
    else
        set_texture(game, split[0], split[1]);
    free_split(split);
}

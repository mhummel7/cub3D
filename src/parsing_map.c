/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:28:22 by mhummel           #+#    #+#             */
/*   Updated: 2025/04/02 16:19:55 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_map_lines(t_game *game, char *line, int fd, int *i)
{
	char	*map_line;

	strip_newline(line);
	game->map[*i] = ft_strdup(line);
	if (!game->map[*i])
		error_exit("Malloc failed for map line");
	(*i)++;
	map_line = get_next_line(fd);
	while (map_line != NULL)
	{
		strip_newline(map_line);
		if (ft_strlen(map_line) == 0)
		{
			free(map_line);
			break ;
		}
		game->map[*i] = ft_strdup(map_line);
		if (!game->map[*i])
			error_exit("Malloc failed for map line");
		free(map_line);
		(*i)++;
		map_line = get_next_line(fd);
	}
}

static void	set_map_width(t_game *game)
{
	int	i;
	int	len;

	i = 0;
	while (i < game->map_height)
	{
		len = ft_strlen(game->map[i]);
		if (len > game->map_width)
			game->map_width = len;
		i++;
	}
}

void	parse_map(t_game *game, char *line, int fd)
{
	int	i;

	i = 0;
	game->map = malloc(sizeof(char *) * 100);
	if (!game->map)
		error_exit("Malloc failed");
	parse_map_lines(game, line, fd, &i);
	game->map_height = i;
	game->map[i] = NULL;
	set_map_width(game);
	validate_map(game);
}

static void	handle_line(char *line, t_game *game, int *map_started, int fd)
{
	if (ft_strlen(line) == 0)
	{
		if (!*map_started)
			return ;
		*map_started = 2;
	}
	else if (is_map_line(line) && !*map_started)
	{
		*map_started = 1;
		parse_map(game, line, fd);
	}
	else if (!*map_started)
		parse_element(game, line);
}

void	parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		map_started;

	fd = open(filename, O_RDONLY);
	map_started = 0;
	if (fd < 0)
		error_exit("Cannot open file");
	line = get_next_line(fd);
	while (line != NULL && map_started != 2)
	{
		strip_newline(line);
		handle_line(line, game, &map_started, fd);
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!game->no_texture || !game->so_texture || !game->we_texture
		|| !game->ea_texture || !game->map)
		error_exit("Missing required elements");
}

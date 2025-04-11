/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:28:22 by mhummel           #+#    #+#             */
/*   Updated: 2025/04/11 11:36:07 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	parse_cub_file_init(char *filename, t_game *game, int *fd,
		int *map_started)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		error_exit("Cannot open file");
	game->filename = ft_strdup(filename);
	if (!game->filename)
	{
		close(*fd);
		error_exit("Malloc failed for filename");
	}
	*map_started = 0;
}

void	parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		map_started;

	parse_cub_file_init(filename, game, &fd, &map_started);
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
		error_exit_game("Missing required elements", game);
}

static int	count_map_lines(int fd)
{
	int		map_size;
	char	*temp_line;

	map_size = 1;
	temp_line = get_next_line(fd);
	while (temp_line != NULL)
	{
		strip_newline(temp_line);
		if (ft_strlen(temp_line) == 0)
		{
			free(temp_line);
			break ;
		}
		if (is_map_line(temp_line))
			map_size++;
		free(temp_line);
		temp_line = get_next_line(fd);
	}
	return (map_size);
}

static void	allocate_map(t_game *game, int map_size)
{
	game->map = malloc(sizeof(char *) * (map_size + 1));
	if (!game->map)
		error_exit_game("Malloc failed for map allocation", game);
}

static int	prepare_map(t_game *game, int fd, int *new_fd)
{
	int	map_size;

	if (!game->filename)
	{
		close(fd);
		error_exit_game("Filename not set", game);
	}
	map_size = count_map_lines(fd);
	allocate_map(game, map_size);
	close(fd);
	*new_fd = open(game->filename, O_RDONLY);
	if (*new_fd < 0)
	{
		close(*new_fd);
		error_exit_game("Cannot reopen file", game);
	}
	return (map_size);
}

void	parse_map(t_game *game, char *line, int fd)
{
	int	map_size;
	int	new_fd;

	map_size = prepare_map(game, fd, &new_fd);
	skip_to_map(new_fd, &line);
	if (!line)
	{
		close(new_fd);
		error_exit_game("No valid map line found", game);
	}
	read_map_lines(game, line, new_fd, map_size);
	free(line);
	game->map[map_size] = NULL;
	game->map_height = map_size;
	set_map_width(game);
	validate_map(game);
	close(new_fd);
}

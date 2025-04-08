/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:54:57 by mhummel           #+#    #+#             */
/*   Updated: 2025/04/07 12:29:49 by mhummel          ###   ########.fr       */
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

void	set_map_width(t_game *game)
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

bool check_not_set_variable(t_game *game)
{
	if (!game->no_tex || !game->ea_tex || !game->so_tex || !game->no_tex ||
	!game->floor_color || !game->ceiling_color)
	{
		return (false);
	}
	return (true);
}

void	handle_line(char *line, t_game *game, int *map_started, int fd)
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

void	read_map_lines(t_game *game, char *line, int fd, int map_size)
{
	int		i;
	char	*temp_line;

	i = 0;
	strip_newline(line);
	game->map[i] = ft_strdup(line);
	if (!game->map[i])
		error_exit("Malloc failed for map line");
	i++;
	while (i < map_size)
	{
		temp_line = get_next_line(fd);
		if (!temp_line || ft_strlen(temp_line) == 0)
			break ;
		strip_newline(temp_line);
		game->map[i] = ft_strdup(temp_line);
		if (!game->map[i])
			error_exit("Malloc failed for map line");
		free(temp_line);
		i++;
	}
}

void	skip_to_map(int fd, char **line)
{
	char	*temp_line;

	temp_line = get_next_line(fd);
	while (temp_line != NULL)
	{
		strip_newline(temp_line);
		if (is_map_line(temp_line))
		{
			*line = temp_line;
			return ;
		}
		free(temp_line);
		temp_line = get_next_line(fd);
	}
	*line = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:28:38 by mhummel           #+#    #+#             */
/*   Updated: 2025/04/02 16:20:23 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int is_map_line(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (!is_valid_char(line[i]))
            return (0);
        i++;
    }
    return (i > 0);
}

void set_player_position(t_game *game, int i, int j, int *player_count)
{
    char c = game->map[i][j];
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        (*player_count)++;
        game->pos_x = j + 0.5;
        game->pos_y = i + 0.5;
        printf("Player found at [%d][%d]: %c, pos_x: %f, pos_y: %f\n", i, j, c, game->pos_x, game->pos_y);
        if (c == 'N')
        {
            game->dir_x = 0;
            game->dir_y = -1;
        }
        else if (c == 'S')
        {
            game->dir_x = 0;
            game->dir_y = 1;
        }
        else if (c == 'E')
        {
            game->dir_x = 1;
            game->dir_y = 0;
        }
        else if (c == 'W')
        {
            game->dir_x = -1;
            game->dir_y = 0;
        }
    }
}

int check_enclosure(t_game *game, int i, int j)
{
    int len = ft_strlen(game->map[i]);
    char c = game->map[i][j];
    if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        if (i == 0 || i == game->map_height - 1 || j == 0 || j == len - 1)
            return (0);
        if (!is_valid_char(game->map[i - 1][j]) || game->map[i - 1][j] == ' ')
            return (0);
        if (!is_valid_char(game->map[i + 1][j]) || game->map[i + 1][j] == ' ')
            return (0);
        if (j > 0 && (!is_valid_char(game->map[i][j - 1]) || game->map[i][j - 1] == ' '))
            return (0);
        if (j < len - 1 && (!is_valid_char(game->map[i][j + 1]) || game->map[i][j + 1] == ' '))
            return (0);
    }
    return (1);
}

void validate_map(t_game *game)
{
    int i;
    size_t j;
    int player_count = 0;

    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        printf("Validating row %d: %s\n", i, game->map[i]);
        while (j < ft_strlen(game->map[i]))
        {
            if (!is_valid_char(game->map[i][j]))
                error_exit("Invalid character in map");
            if (!check_enclosure(game, i, j))
                error_exit("Map not enclosed by walls");
            set_player_position(game, i, j, &player_count);
            j++;
        }
        i++;
    }
    if (player_count != 1)
        error_exit("Map must have exactly one player position");
    printf("Map validation successful, player_count: %d\n", player_count);
}

// #include "../includes/cub3d.h"

// int	is_valid_char(char c)
// {
// 	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
// 		|| c == ' ');
// }

// int	is_map_line(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (!is_valid_char(line[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (i > 0);
// }

// void	set_player_position(t_game *game, int i, int j, int *player_count)
// {
// 	char	c;

// 	c = game->map[i][j];
// 	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
// 	{
// 		(*player_count)++;
// 		game->pos_x = j + 0.5;
// 		game->pos_y = i + 0.5;
// 		if (c == 'N')
// 		{
// 			game->dir_x = 0;
// 			game->dir_y = -1;
// 		}
// 		else if (c == 'S')
// 		{
// 			game->dir_x = 0;
// 			game->dir_y = 1;
// 		}
// 		else if (c == 'E')
// 		{
// 			game->dir_x = 1;
// 			game->dir_y = 0;
// 		}
// 		else if (c == 'W')
// 		{
// 			game->dir_x = -1;
// 			game->dir_y = 0;
// 		}
// 	}
// }

// int	check_enclosure(t_game *game, int i, int j)
// {
// 	int		len;
// 	char	c;

// 	len = ft_strlen(game->map[i]);
// 	c = game->map[i][j];
// 	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
// 	{
// 		if (i == 0 || i == game->map_height - 1 || j == 0 || j == len - 1)
// 			return (0);
// 		if (!is_valid_char(game->map[i - 1][j]) || game->map[i - 1][j] == ' ')
// 			return (0);
// 		if (!is_valid_char(game->map[i + 1][j]) || game->map[i + 1][j] == ' ')
// 			return (0);
// 		if (j > 0 && (!is_valid_char(game->map[i][j - 1]) || game->map[i][j
// 				- 1] == ' '))
// 			return (0);
// 		if (j < len - 1 && (!is_valid_char(game->map[i][j + 1])
// 				|| game->map[i][j + 1] == ' '))
// 			return (0);
// 	}
// 	return (1);
// }

// void	validate_map(t_game *game)
// {
// 	int		i;
// 	size_t	j;
// 	int		player_count;

// 	i = 0;
// 	player_count = 0;
// 	while (i < game->map_height)
// 	{
// 		j = 0;
// 		while (j < ft_strlen(game->map[i]))
// 		{
// 			if (!is_valid_char(game->map[i][j]))
// 				error_exit("Invalid character in map");
// 			if (!check_enclosure(game, i, j))
// 				error_exit("Map not enclosed by walls");
// 			set_player_position(game, i, j, &player_count);
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (player_count != 1)
// 		error_exit("Map must have exactly one player position");
// }

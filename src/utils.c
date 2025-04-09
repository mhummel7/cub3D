/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:28:51 by mhummel           #+#    #+#             */
/*   Updated: 2025/04/09 15:33:56 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_exit(const char *message)
{
	write(2, "Error: ", 7);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	error_exit_game(const char *message, t_game *game)
{
	write(2, "Error: ", 7);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	if (game)
		free_game2(game);
	exit(EXIT_FAILURE);
}

void	strip_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

void	free_split_error_exit(char **values)
{
	free_split(values);
	error_exit("RGB values must be in range [0,255]");
}

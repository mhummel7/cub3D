/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:23:51 by mhummel           #+#    #+#             */
/*   Updated: 2025/04/14 10:11:35 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	count_map_lines(int fd)
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

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
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

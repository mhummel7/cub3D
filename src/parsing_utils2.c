/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:23:51 by mhummel           #+#    #+#             */
/*   Updated: 2025/04/09 15:24:07 by mhummel          ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb_floor_ceiling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frocha <frocha@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:41:19 by frocha            #+#    #+#             */
/*   Updated: 2025/04/05 18:41:20 by frocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_valid_values(int *rgb)
{
	int	k;

	k = 0;
	while (k < 3)
	{
		if (rgb[k] < 0 || rgb[k] > 255)
			error_exit("RGB values must be in range [0,255]");
		k++;
	}
}

void	parse_rgb_values(char **line, int *rgb)
{
	int		i;
	int		component;
	char	**values;
	int		j;

	i = 0;
	component = 0;
	while (line[i] && component < 3)
	{
		values = ft_split(line[i], ',');
		j = 0;
		while (values[j] && component < 3)
		{
			rgb[component] = ft_atoi(values[j]);
			component++;
			j++;
		}
		free_split(values);
		i++;
	}
}

int	get_rgb(char **line)
{
	int rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	parse_rgb_values(line, rgb);
	check_valid_values(rgb);
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
}
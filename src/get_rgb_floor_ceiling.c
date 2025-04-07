/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb_floor_ceiling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:41:19 by frocha            #+#    #+#             */
/*   Updated: 2025/04/07 11:51:12 by mhummel          ###   ########.fr       */
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

bool	incorrect_value_between(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || (33 < str[i] && str[i] < 47))
			return (true);
		i++;
	}
	return (false);
}

void check_free_possible(char	**values, int component)
{
	free_split(values);
	if (component < 3)
		error_exit("Not at values were setted");
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
			if (incorrect_value_between(values[j]))
			{
				free_split(values);
				error_exit("RGB values must be in range [0,255]");
			}
			rgb[component] = ft_atoi(values[j]);
			component++;
			j++;
		}
		check_free_possible(values, component);
		i++;
	}
}

int	get_rgb(char **line)
{
	int	rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	parse_rgb_values(line, rgb);
	check_valid_values(rgb);
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
}

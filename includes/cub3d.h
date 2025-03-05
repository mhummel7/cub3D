/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:54:21 by mhummel           #+#    #+#             */
/*   Updated: 2025/03/05 14:28:41 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/libft.h"
#include "../libft/get_next_line.h"
#include "../MLX42/include/MLX42/MLX42.h" // MLX42 header
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

# define WIDTH		1920
# define HEIGHT		1080

typedef struct s_game
{
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
	int floor_color;
	int ceiling_color;
	char **map;
	int map_height;
	int map_width;
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	mlx_t *mlx;
	mlx_image_t *img; // For rendering
} t_game;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:54:21 by mhummel           #+#    #+#             */
/*   Updated: 2025/03/13 11:43:40 by mhummel          ###   ########.fr       */
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

# define WIDTH		2580
# define HEIGHT		1960
# define CUBE_SIZE  20
# define MOVING_OBJECT_SIZE 5

typedef struct s_game
{
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
	mlx_texture_t *no_tex; // Loaded North texture
	mlx_texture_t *so_tex; // Loaded South texture
	mlx_texture_t *we_tex; // Loaded West texture
	mlx_texture_t *ea_tex; // Loaded East texture
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
	mlx_image_t *static_layer;
	mlx_image_t *dynamic_layer; // For rendering
	float ray_dir_x; // Ray direction vector
    float ray_dir_y;
    float plane_x;   // Camera plane (for FOV)
    float plane_y;
} t_game;

// parsing_elements.c
void parse_element(t_game *game, char *line);
int get_rgb(char *line);

// parsing_map.c
void parse_cub_file(char *filename, t_game *game);
void parse_map(t_game *game, char *line, int fd);
void parse_map_lines(t_game *game, char *line, int fd, int *i);

// validate_map.c
void validate_map(t_game *game);
int check_enclosure(t_game *game, int i, int j);
void set_player_position(t_game *game, int i, int j, int *player_count);
int is_map_line(char *line);
int is_valid_char(char c);

// utils.c
void error_exit(const char *message);
void strip_newline(char *line);

// free.c
void free_game(t_game *game);

// main.c
void init_game(t_game *game);
bool check_collision(t_game *game, int new_x, int new_y);

// mlx_utils.c
void handle_movement(t_game *game, mlx_key_data_t keydata, double move_speed);
void handle_strafe(t_game *game, mlx_key_data_t keydata, double move_speed);
void handle_rotation(t_game *game, mlx_key_data_t keydata, double rot_speed);
void init_mlx(t_game *game);
void update_player(t_game *game, double move_speed, double rot_speed);

#endif

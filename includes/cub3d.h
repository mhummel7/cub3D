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
# define PI 3.14159265358979323846

typedef enum e_dir
{
	X_DIR,
	Y_DIR,
}	t_dir;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_assets
{
	char			*no;	//filename to NO asset
	char			*ea;
	char			*so;
	char			*we;
	uint32_t		c;		//color ceiling
	uint32_t		f;		//color floor
	bool			c_set;
	bool			f_set;
	int				err;
	int				i;
}					t_assets;

typedef struct s_game
{
	t_assets		*assets;
	mlx_image_t	*wall_image;
	mlx_texture_t *no_tex; // Loaded North texture
	mlx_texture_t *so_tex; // Loaded South texture
	mlx_texture_t *we_tex; // Loaded West texture
	mlx_texture_t *ea_tex; // Loaded East texture
	float player_angle;
	int width;
	int height;
	t_vector		pos_player;
	t_vector		dir_player;
	t_vector		ray_dir;
	t_vector		plane;
	char **map;
	int map_height;
	int map_width;
	mlx_t *mlx;
	mlx_image_t *static_layer;
	mlx_image_t *dynamic_layer; // For rendering
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

// mlx_utils.c
void init_mlx(t_game *game);

//add_static_objects.c
void add_static_pixels(t_game *game);
void process_map_row(t_game *game, int i, int *base_x_mult, int *base_y_mult);
void set_player_location(t_game *game, int base_x_mult, int base_y_mult, char cell);
void draw_walls(t_game *game, int base_x_mult, int base_y_mult);

#endif

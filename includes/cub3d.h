/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:42:11 by frocha            #+#    #+#             */
/*   Updated: 2025/04/03 13:02:00 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SCREEN_WIDTH 1300
# define SCREEN_HEIGHT 800
# define CUBE_SIZE 16
# define MOVING_OBJECT_SIZE 1
# define FOV_ANGLE (60 * (PI / 180))
# define PI 3.14159265
# define TWO_PI 6.28318530
# define NUM_RAYS 1300
// # define MAP_NUM_ROWS 6
// # define MAP_NUM_COLS 15
// # define WINDOW_WIDTH (MAP_NUM_COLS * CUBE_SIZE)
// # define WINDOW_HEIGHT (MAP_NUM_ROWS * CUBE_SIZE)

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
	uint32_t floor_color;
	uint32_t ceiling_color;
	char **map;
	int map_height;
	int map_width;
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	mlx_t		*mlx;
	mlx_image_t	*static_layer;
	mlx_image_t	*dynamic_layer;
	mlx_image_t	*background_layer;
	mlx_image_t	*wall_layer;
	uint32_t *color_buffer;
	int window_width;
	int window_height;
}				t_game;

typedef struct s_map
{
	char		**grid;
	int			map_height;
	int			map_width;
}				t_map;

typedef struct s_player
{
	float		x;
	float		y;
	int			turn_direction;
	int			walk_direction;
	int			diagonal_direction;
	float		rotation_angle;
	float		walk_speed;
	float		turn_speed;
	t_game		*game;
	t_map		*map;
}				t_player;

typedef struct Ray
{
	float		ray_angle;
	float		wall_hit_x;
	float		wall_hit_y;
	float		distance;
	int			was_hit_vertical;
	int			is_ray_facing_up;
	int			is_ray_facing_down;
	int			is_ray_facing_left;
	int			is_ray_facing_right;
}	t_rays[NUM_RAYS];

typedef struct s_str_access
{
	t_player	*player;
	t_map		*map;
	t_game		*game;
}				t_str_access;

typedef struct s_horz_wall_hit_data
{
	int			found_horz_hit;
	float		horz_hit_x;
	float		horz_hit_y;
}				t_horz_wall_hit_data;

typedef struct s_vert_wall_hit_data
{
	int			found_vert_hit;
	float		vert_hit_x;
	float		vert_hit_y;
}				t_vert_wall_hit_data;

typedef struct s_ray_facing_data
{
	int			is_ray_facing_down;
	int			is_ray_facing_up;
	int			is_ray_facing_right;
	int			is_ray_facing_left;
}				t_ray_facing_data;

typedef struct s_hit_distance_wall
{
	float		horz;
	float		vert;
}				t_hit_distance_wall;

typedef struct s_ray_wall_hit_horz
{
	float		x_intercept;
	float		y_intercept;
	float		y_step;
	float		x_step;
	float		next_horz_touch_wall_x;
	float		next_horz_touch_wall_y;
	float		x_to_check;
	float		y_to_check;
}				t_ray_wall_hit_horz;

typedef struct s_ray_wall_hit_vert
{
	float		x_intercept;
	float		y_intercept;
	float		y_step;
	float		x_step;
	float		next_vert_touch_wall_x;
	float		next_vert_touch_wall_y;
	float		y_to_check;
	float		x_to_check;
}				t_ray_wall_hit_vert;

typedef struct s_draw_line_variables
{
	int			init_x;
	int			init_y;
	int			dest_x;
	int			dest_y;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
}				t_draw_line_variables;

void			draw_line(t_player *player, t_game *game, float dest_x,
					float dest_y);

// parsing_map.c */
void			parse_cub_file(char *filename, t_game *game);
void			parse_map(t_game *game, char *line, int fd);
void			parse_map_lines(t_game *game, char *line, int fd, int *i);

// free.c */
void			free_game(t_game *game);

// utils.c */
void			error_exit(const char *message);
void			strip_newline(char *line);

// parsing_elements.c
void parse_element(t_game *game, char *line);
int get_rgb(char *line);

// validate_map.c
void validate_map(t_game *game);
int check_enclosure(t_game *game, int i, int j);
void set_player_position(t_game *game, int i, int j, int *player_count);
int is_map_line(char *line);
int is_valid_char(char c);

// init
void			init_game(t_game *game);

/* initiate_struct_values.c */
void			initiate_map(t_map *map, char *filename, t_game *game);
void			initiate_player(t_player *player, t_game *game);
void			initiate_str_access_values(t_str_access *str_access);
void			set_player_rotation_angle(t_player *player, char letter);

/* player_functions.c */
void			move_player(t_player *player);

/* map_wall_functions.c */
void			add_static_pixels(t_str_access *str_access);
void			process_map_row(t_str_access *str_access, int i,
					int *base_x_mult, int *base_y_mult);
void			draw_walls(t_game *game, int base_x_mult, int base_y_mult);
int				check_obstacle_blocks(float new_player_x, float new_player_y,
					t_player *player);
int				is_wall(float x, float y, t_player *player);

/* draw_rays.c */
void			cast_all_rays(t_player *player, t_rays *rays);
void			render_rays(t_player *player, t_rays *rays);
int				distance_ray2wall(float origin_x, float origin_y,
					float destination_x, float destination_y);

/* ray_wall_hit.c */
void			find_horz_ray_wall_hit(t_horz_wall_hit_data *horz_wall_hit_data,
					float ray_angle, t_player *player,
					t_ray_facing_data *ray_facing_data);
void			find_vert_ray_wall_hit(t_vert_wall_hit_data *vert_wall_hit_data,
					float ray_angle, t_player *player,
					t_ray_facing_data *ray_facing_data);
void			inititate_ray_direction_data(t_ray_facing_data *ray_facing_data,
					float ray_angle);
void			find_distance(t_hit_distance_wall *hit_distance_wall,
					t_horz_wall_hit_data *horz_wall_hit_data,
					t_vert_wall_hit_data *vert_wall_hit_data, t_player *player);
void			init_wall_hit_data_values(t_horz_wall_hit_data *horz_hit_data,
					t_vert_wall_hit_data *vert_hit_data);

/* set_values_each_ray.c */
void			set_values_ray(t_rays *rays, float ray_angle,
					t_ray_facing_data *ray_facing_data, int counter);
void			set_vert_values_ray(t_rays *rays,
					t_hit_distance_wall *hit_distance_wall,
					t_vert_wall_hit_data *vert_wall_hit_data, int counter);
void			set_horz_values_ray(t_rays *rays,
					t_hit_distance_wall *hit_distance_wall,
					t_horz_wall_hit_data *horz_wall_hit_data, int counter);

/* find_intercepts_steps.c */
void			find_horz_intercepts(t_ray_wall_hit_horz *horz_ray_data,
					float ray_angle, t_player *player,
					t_ray_facing_data *ray_facing_data);
void			find_horz_steps(t_ray_wall_hit_horz *horz_ray_data,
					float ray_angle, t_ray_facing_data *ray_facing_data);
void			find_vert_intercepts(t_ray_wall_hit_vert *vert_ray_data,
					float ray_angle, t_player *player,
					t_ray_facing_data *ray_facing_data);
void			find_vert_steps(t_ray_wall_hit_vert *vert_ray_data,
					float ray_angle, t_ray_facing_data *ray_facing_data);

/* check_ray_between_limits.c */
bool			check_limits_horz_ray(t_ray_wall_hit_horz *horz_ray_data, t_game *game);
bool			check_limits_vert_ray(t_ray_wall_hit_vert *vert_ray_data, t_game *game);

/* set_dir_player_pos.c */
void set_dir_player_pos(t_game *game, int x, int y);
int set_texture_direction(char **texture_char, mlx_texture_t **texture, char *value);

/* init_structs.h */
void	init_mlx(t_game *game);
void init_game(t_game *game);

/* generate_3d.c */
uint32_t get_mlx_texture_color(mlx_texture_t* texture, int x, int y);
void generate3Dprojection(t_rays *rays, t_player *player);

/*keys_hook.c*/
void	keys_hook(mlx_key_data_t keydata, void *param);

#endif

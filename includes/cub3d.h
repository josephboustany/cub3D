/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:08:03 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/22 21:03:49 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_W 1920
# define SCREEN_H 1080
# define K_ESC 65307
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_LEFT 65361
# define K_RIGHT 65363
# define R_SPEED 0.01
# define M_SPEED 0.012

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <mlx.h>
# include <X11/keysym.h>

typedef enum s_line_type
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
	MAP,
	EMPTY,
	ERROR
}	t_line_type;

typedef struct s_check
{
	char	**map_dup;
	int		*pos_x;
	int		*pos_y;
	int		start;
	int		end;
}	t_check;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
	int		floor_color;
	int		ceiling_color;
}	t_map;

typedef struct s_tex
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		line_len;
	int		bpp;
	int		endian;
}	t_tex;

typedef struct s_game
{
	char	**grid;
	void	*mlx;
	void	*win;
	int		floor_color;
	int		ceiling_color;
	int		keys[6];
	t_tex	north;
	t_tex	south;
	t_tex	east;
	t_tex	west;
	t_tex	screen;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_game;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

// args1.c
int				check_num_of_args(int argc);
int				check_if_cub(char *argv);
void			validate_args(int argc, char **argv);
// parsing1.c
int				cub_size(char *cub_name);
char			*cub_to_str(char *cub_name);
int				count_lines(char *str);
char			**allocate_array(int lines);
char			*get_line(char *str, int i);
// parsing2.c
char			**fill_array(char *cub_map);
char			*skip_spaces(char *line);
int				line_is_empty(char *line);
int				is_map(char c);
t_line_type		identify_line_type(char *line);
// parsing3.c
t_map			*allocate_map_struct(char **array);
int				skip_spaces_descript(char *array);
char			*extract_path_from_line(char *array, t_map *map_data);
void			assign_texture(char **texture,
					char *line, t_map *map_data, char *err);
void			handle_texture_line(t_line_type type,
					char *line, t_map *map_data);
// parsing4.c
void			get_paths(char **array, t_map *map_data);
int				parse_rgb_value(char *s, int *i);
int				create_rgb(char *array, t_map *map_data);
void			get_color(char **array, t_map *map_data);
int				find_map_index(char **array);
// parsing5.c
void			get_width(char **array, t_map *map_data);
void			get_height(char **array, t_map *map_data);
void			allocate_grid(char **array, t_map *map_data);
void			get_map_line(char *array, t_map *map_data, int grid_index);
t_map			*get_map_data(char *cub_name);
// parsing6.c
void			validate_texture_path(char *path, char *error, t_map *map_data);
void			check_paths(t_map *map_data);
void			check_all_map_data(t_map *map_data);
// map1.c
int				is_space(t_map *map_data, int y, int x);
int				is_player(t_map *map_data, int y, int x);
int				is_floor(t_map *map_data, int y, int x);
int				is_wall(t_map *map_data, int y, int x);
void			check_map_chars(t_map *map_data);
// map2.c
void			check_if_one_player(t_map *map_data);
char			**alloc_map_dup(t_map *map_data);
t_check			*alloc_map_check(t_map *map_data);
void			locate_player(t_map *map_data, t_check *map_check);
void			duplicate_map(t_map *map_data, t_check *map_check);
// flood1.c
t_check			*create_map_check(t_map *map_data);
int				check_up(t_check *map_check, int x, int y, t_map *map_data);
int				check_down(t_check *map_check, int x, int y, t_map *map_data);
int				check_left(t_check *map_check, int x, int y, t_map *map_data);
int				check_right(t_check *map_check, int x, int y, t_map *map_data);
// flood2.c
void			final_check(t_check *map_check, t_map *map_data);
void			mark_as_visited(t_check *map_check, int x, int y);
void			add_to_list(t_check *map_check, int x, int y);
int				flood_fill(t_check *map_check, t_map *map_data);
void			validate_map(t_map *map_data);
// minilib1.c
t_game			*create_t_game(t_map *map_data);
void			load_texture(t_game *game, t_tex *tex, char *path);
void			load_textures(t_map *map_data, t_game *game);
void			pixel_put(t_tex *screen, int x, int y, int color);
void			init_screen_buffer(t_game *game);
// minilib2.c
void			set_east_west(t_game *game, char c);
void			set_north_south(t_game *game, char c);
void			set_direction(t_game *game, char c);
void			set_player_pos(t_map *map_data, t_game *game);
int				keyboard_keys(int keycode, void *param);
//minilib3.c
int				close_with_x(t_game *game);
void			rotate_player(t_game *game, double dir);
void			move_player(t_game *game, double dir);
void			strafe_player(t_game *game, double dir);
void			start_game(t_game *game);
// minilib4.c
int				key_release(int keycode, void *param);
void			process_keys(t_game *game);
// raycast1.c
int				render_frame(void *param);
void			init_ray(t_game *game, t_ray *ray, int x);
void			dda_setup(t_game *game, t_ray *ray);
void			dda_run(t_game *game, t_ray *ray);
void			get_wall_dist(t_ray *ray);
// raycast2.c
void			cast_ray(t_game *game, t_ray *ray, int x);
t_tex			*get_tex(t_game *game, t_ray *ray);
int				get_tex_x(t_game *game, t_ray *ray, t_tex *tex);
void			calc_draw_range(t_ray *ray);
void			draw_ceiling_floor(t_game *game, t_ray *ray, int x);
// raycast3.c
void			draw_wall_strip(t_game *game, t_ray *ray, t_tex *tex, int x);
void			draw_column(t_game *game, t_ray *ray, int x);
// utils1.c
int				ft_strlen(char *str);
int				ft_strncmp(char *str1, char *str2, int n);
int				ft_atoi(const char *nptr);
void			free_array(char **array);
void			error_exit(char *message);
// utils2.c
void			free_map_data(t_map *map_data);
void			free_and_exit(t_map *map_data, char *message);
void			free_exit2(t_map *map_data, t_check *map_check, char *message);
void			final_exit(t_game *game, char *message);
void			final_exit2(t_game *game);
#endif